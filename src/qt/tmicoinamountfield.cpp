// Copyright (c) 2011-2015 The TMIcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "tmicoinamountfield.h"

#include "tmicoinunits.h"
#include "guiconstants.h"
#include "qvaluecombobox.h"
#include "../policy/policy.h"

#include <QApplication>
#include <QAbstractSpinBox>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include <QLabel>

/** QSpinBox that uses fixed-point numbers internally and uses our own
 * formatting/parsing functions.
 */
class AmountSpinBox: public QAbstractSpinBox
{
    Q_OBJECT

public:
    explicit AmountSpinBox(QWidget *parent):
        QAbstractSpinBox(parent),
        currentUnit(TMIcoinUnits::TMI),
        singleStep(TRANSACTION_FEE_DENOMINATOR) // satoshis
    {
        setAlignment(Qt::AlignRight);

        connect(lineEdit(), SIGNAL(textEdited(QString)), this, SIGNAL(valueChanged()));
    }

    QValidator::State validate(QString &text, int &pos) const
    {
        if(text.isEmpty())
            return QValidator::Intermediate;
        bool valid = false;
        parse(text, &valid);
        
        // IsAllowedDustAmount 관련 입력 상태 동적 반영 목적의 코드
        if(!valid) {
            CAmount val = 0;
            if(TMIcoinUnits::parse(currentUnit, text, &val, false) && !IsAllowedDustAmount(val)) {
                QStringList parts = TMIcoinUnits::removeSpaces(text).split(".");
                if (parts.size() == 2) {
                    const int num_decimals = TMIcoinUnits::decimalsLength(currentUnit) - TMIcoinUnits::decimal_display_decrease();
                    if (0 < num_decimals && parts[1].size() > num_decimals) {
                        QString temp = parts[0] + "." + parts[1].leftJustified(num_decimals, '0', true);
                        parse(temp, &valid);
                        if (valid)
                            text = temp;
                    }
                }
            }
        }

        /* Make sure we return Intermediate so that fixup() is called on defocus */
        return valid ? QValidator::Intermediate : QValidator::Invalid;
    }

    void fixup(QString &input) const
    {
        bool valid = false;
        CAmount val = parse(input, &valid);
        if(valid)
        {
            input = TMIcoinUnits::format(currentUnit, val, false, TMIcoinUnits::separatorAlways, true);
            lineEdit()->setText(input);
        }
    }

    CAmount value(bool *valid_out=0) const
    {
        return parse(text(), valid_out);
    }

    void setValue(const CAmount& value)
    {
        lineEdit()->setText(TMIcoinUnits::format(currentUnit, value, false, TMIcoinUnits::separatorAlways, true));
        Q_EMIT valueChanged();
    }

    void stepBy(int steps)
    {
        bool valid = false;
        CAmount val = value(&valid);
        val = val + steps * singleStep;
        val = qMin(qMax(val, CAmount(0)), TMIcoinUnits::maxMoney());
        setValue(val);
    }

    void setDisplayUnit(int unit)
    {
        bool valid = false;
        CAmount val = value(&valid);

        currentUnit = unit;

        if(valid)
            setValue(val);
        else
            clear();
    }

    void setSingleStep(const CAmount& step)
    {
        singleStep = step;
    }

    QSize minimumSizeHint() const
    {
        if(cachedMinimumSizeHint.isEmpty())
        {
            ensurePolished();

            const QFontMetrics fm(fontMetrics());
            int h = lineEdit()->minimumSizeHint().height();
            int w = fm.width(TMIcoinUnits::format(TMIcoinUnits::TMI, TMIcoinUnits::maxMoney(), false, TMIcoinUnits::separatorAlways, true));
            w += 2; // cursor blinking space

            QStyleOptionSpinBox opt;
            initStyleOption(&opt);
            QSize hint(w, h);
            QSize extra(35, 6);
            opt.rect.setSize(hint + extra);
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt,
                                                    QStyle::SC_SpinBoxEditField, this).size();
            // get closer to final result by repeating the calculation
            opt.rect.setSize(hint + extra);
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt,
                                                    QStyle::SC_SpinBoxEditField, this).size();
            hint += extra;
            hint.setHeight(h);

            opt.rect = rect();

            cachedMinimumSizeHint = style()->sizeFromContents(QStyle::CT_SpinBox, &opt, hint, this)
                                    .expandedTo(QApplication::globalStrut());
        }
        return cachedMinimumSizeHint;
    }

private:
    int currentUnit;
    CAmount singleStep;
    mutable QSize cachedMinimumSizeHint;

    /**
     * Parse a string into a number of base monetary units and
     * return validity.
     * @note Must return 0 if !valid.
     */
    CAmount parse(const QString &text, bool *valid_out=0) const
    {
        CAmount val = 0;
        bool valid = TMIcoinUnits::parse(currentUnit, text, &val, true);
        if(valid)
        {
            if(val < 0 || val > TMIcoinUnits::maxMoney())
                valid = false;
        }
        if(valid_out)
            *valid_out = valid;
        return valid ? val : 0;
    }

protected:
    bool event(QEvent *event)
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Comma)
            {
                // Translate a comma into a period
                QKeyEvent periodKeyEvent(event->type(), Qt::Key_Period, keyEvent->modifiers(), ".", keyEvent->isAutoRepeat(), keyEvent->count());
                return QAbstractSpinBox::event(&periodKeyEvent);
            }
        }
        return QAbstractSpinBox::event(event);
    }

    StepEnabled stepEnabled() const
    {
        if (isReadOnly()) // Disable steps when AmountSpinBox is read-only
            return StepNone;
        if (text().isEmpty()) // Allow step-up with empty field
            return StepUpEnabled;

        StepEnabled rv = 0;
        bool valid = false;
        CAmount val = value(&valid);
        if(valid)
        {
            if(val > 0)
                rv |= StepDownEnabled;
            if(val < TMIcoinUnits::maxMoney())
                rv |= StepUpEnabled;
        }
        return rv;
    }

Q_SIGNALS:
    void valueChanged();
};

#include "tmicoinamountfield.moc"

TMIcoinAmountField::TMIcoinAmountField(QWidget *parent) :
    QWidget(parent),
    amount(0)
{
    amount = new AmountSpinBox(this);
    amount->setLocale(QLocale::c());
    amount->installEventFilter(this);
    amount->setMaximumWidth(170);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(amount);
    amountUnit = new QLabel(this);
    layout->addWidget(amountUnit);
    //unit = new QValueComboBox(this);
    //unit->setModel(new TMIcoinUnits(this));
    //layout->addWidget(unit);
    layout->addStretch(1);
    layout->setContentsMargins(0,0,0,0);

    setLayout(layout);

    setFocusPolicy(Qt::TabFocus);
    setFocusProxy(amount);

    // If one if the widgets changes, the combined content changes as well
    connect(amount, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
    //connect(unit, SIGNAL(currentIndexChanged(int)), this, SLOT(unitChanged(int)));

    // Set default based on configuration
    //unitChanged(unit->currentIndex());
    unitChanged(0);
}

void TMIcoinAmountField::clear()
{
    amount->clear();
    //unit->setCurrentIndex(0);
    amountUnit->setText(TMIcoinUnits::name(0));
}

void TMIcoinAmountField::setEnabled(bool fEnabled)
{
    amount->setEnabled(fEnabled);
    //unit->setEnabled(fEnabled);
}

bool TMIcoinAmountField::validate()
{
    bool valid = false;
    value(&valid);
    setValid(valid);
    return valid;
}

void TMIcoinAmountField::setValid(bool valid)
{
    if (valid)
        amount->setStyleSheet("");
    else
        amount->setStyleSheet(STYLE_INVALID);
}

bool TMIcoinAmountField::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        // Clear invalid flag on focus
        setValid(true);
    }
    return QWidget::eventFilter(object, event);
}

QWidget *TMIcoinAmountField::setupTabChain(QWidget *prev)
{
    QWidget::setTabOrder(prev, amount);
    QWidget::setTabOrder(amount, amountUnit);
    return amountUnit;

    //QWidget::setTabOrder(prev, amount);
    //QWidget::setTabOrder(amount, unit);
    //return unit;
}

CAmount TMIcoinAmountField::value(bool *valid_out) const
{
    return amount->value(valid_out);
}

void TMIcoinAmountField::setValue(const CAmount& value)
{
    amount->setValue(value);
}

void TMIcoinAmountField::setReadOnly(bool fReadOnly)
{
    amount->setReadOnly(fReadOnly);
}

void TMIcoinAmountField::unitChanged(int idx)
{
    //// Use description tooltip for current unit for the combobox
    //unit->setToolTip(unit->itemData(idx, Qt::ToolTipRole).toString());
    //
    //// Determine new unit ID
    //int newUnit = unit->itemData(idx, TMIcoinUnits::UnitRole).toInt();
    //
    //amount->setDisplayUnit(newUnit);
    amountUnit->setText(TMIcoinUnits::name(idx));
    amount->setDisplayUnit(idx);
}

void TMIcoinAmountField::setDisplayUnit(int newUnit)
{
    //unit->setValue(newUnit);
    amountUnit->setText(TMIcoinUnits::name(newUnit));
}

void TMIcoinAmountField::setSingleStep(const CAmount& step)
{
    amount->setSingleStep(step);
}
