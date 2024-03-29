#ifndef DEFINE_TMI_H
#define DEFINE_TMI_H

#define TEXT_tmi "tmi"
#define TEXT_TMI "TMI"
#define TEXT_TMI "TMI"

//tmi 네트워크의 최대 코인
#define MAXIMUM_COIN_OF_TMI_NETWORK 92233720368 //소수점 자리수가 있어서 TMI 은 100억 단위가 한계

//블럭 보상 관련 옵션
enum class eBlockRewardOption
{
	FirstMax,	// 최초에 모든 코인 발생
	Everyblock, // 블럭마다 보상 지급
};
#define BLOCK_REWARD_OPTION eBlockRewardOption::FirstMax

//{{ eBlockRewardOption::FirstMax
#define BLOCK_REWARD_FIRST            5 * 100000000 //"BLOCK_REWARD_OPTION == eBlockRewardOption::FirstMax" 경우 사용
//}} eBlockRewardOption::FirstMax

//{{ eBlockRewardOption::Everyblock
//블럭 보상 시작 값
#define BLOCK_REWARD_VALUE            50
//블럭 보상 반감 간격
#define BLOCK_REWARD_HALVING_INTERVAL 210000
//}} eBlockRewardOption::Everyblock

//블럭 보상 확정(보류) 카운트
#define BLOCK_REWARD_MATURITY_HOLD 0

//TMI address base58Prefixes
#define PUBKEY_ADDRESS_MAINNET 135 // w
#define PUBKEY_ADDRESS_TESTNET 127 // t
#define PUBKEY_ADDRESS_REGTEST 122 // r

//default 거래 수수료율
#define DEFAULT_TRANSACTION_FEE_DENOMINATOR 100000   //분모(숫자을 깔끔하게 하기 위해서.)(주의: qt gui 소수점 자릿수 계산에 10의 배수로 가정하고 구현하는 부분이 있음.)
#define DEFAULT_TRANSACTION_FEE_NUMERATOR   13      //분자

#define DEFAULT_TRANSACTION_REQUEST_MINIMUM_UNIT DEFAULT_TRANSACTION_FEE_DENOMINATOR

extern unsigned long TRANSACTION_FEE_DENOMINATOR;
extern unsigned long TRANSACTION_FEE_NUMERATOR;
extern const unsigned long& TRANSACTION_REQUEST_MINIMUM_UNIT;

//경고
#define SHOW_OUT_OF_SYNC_WARNING_SECOND     24*60*60    //qt 지갑에서 마지막 블럭을 받고 24시간이 경과하면 경고가 표시됨.

//블럭에 포함되지 않은 거래의 재전송 간격
#define REBROADCAST_INTERVAL_TIME 10 //기존에는 GetRand(30 * 60) 가 사용됨. 테스트 및 운영에 따라서 조정 필요.

//업데이트 관련
#define UPDATE_VERSION_MANAGEMENT_FILE_PREFIX ""        //테스트가 필요한 경우 이름 바꿔서 사용.
#define UPDATE_RULE "0.1.1.0"
#define DEFAULT_UPDATE_CHECK_INTERVAL_SECOND 60 * 60    // 1시간
#define UPDATE_SITE_ADDRESS "https://wallet-version." TEXT_tmi ".io/app/update/" //wallet-version.tmikor.io
#define UPDATE_VERSION_MANAGEMENT_FILE UPDATE_VERSION_MANAGEMENT_FILE_PREFIX TEXT_tmi "coin-qt.version.xml"


//다음 블럭 사이즈는 운영 이후 값 줄이면 안됨.
extern const unsigned int TMI_MAX_BLOCK_SIZE;
extern const unsigned int TMI_DEFAULT_BLOCK_SIZE;

//GenesisBlock 전자서명 공개키입니다.
extern const char* GenesisBlockSignaturePublicKeyBase64_44_MAINNET;//key당 길이 44
extern const char* GenesisBlockSignaturePublicKeyBase64_44_TESTNET;//key당 길이 44
extern const char* GenesisBlockSignaturePublicKeyBase64_44_REGTEST;//key당 길이 44

//GenesisBlock 서명 값입니다.
extern const char* GenesisBlockSignatureBase64_256_MAINNET; //길이 256
extern const char* GenesisBlockSignatureBase64_256_TESTNET; //길이 256
extern const char* GenesisBlockSignatureBase64_256_REGTEST; //길이 256

//SecretKey 는 GenesisBlock 의 서명을 등록하기 위해서 사용하는 것이므로 GenesisBlockSignatureBase64 등록후 반드시 비워주세요.(분리관리)
extern const char* GenesisBlockSignatureSecretKey_MAINNET; //key당 길이 88
extern const char* GenesisBlockSignatureSecretKey_TESTNET; //key당 길이 88
extern const char* GenesisBlockSignatureSecretKey_REGTEST; //key당 길이 88

//GenesisBlock hash 값
extern const char* CHECK_GENESIS_BLOCK_HASH_MAINNET;
extern const char* CHECK_GENESIS_BLOCK_HASH_TESTNET;
extern const char* CHECK_GENESIS_BLOCK_HASH_REGTEST;
extern const char* CHECK_GENESIS_BLOCK_MERKLEROOT_HASH;


#define GENESIS_BLOCK_TIME_STAMP "The TMI August 5, 2018"
#define DNS_SEED_MAINNET vSeeds.emplace_back("mainnet01." TEXT_tmi ".io", false); vSeeds.emplace_back("mainnet02." TEXT_tmi ".io", false); vSeeds.emplace_back("mainnet03." TEXT_tmi ".io", false);
#define DNS_SEED_TESTNET vSeeds.emplace_back("testnet01." TEXT_tmi ".io", false); vSeeds.emplace_back("testnet02." TEXT_tmi ".io", false); vSeeds.emplace_back("testnet03." TEXT_tmi ".io", false); \
                         vSeeds.emplace_back("testnet01." TEXT_tmi ".com", false); vSeeds.emplace_back("testnet02." TEXT_tmi ".com", false); 
#define DEFAULT_SERVER_PORT 8624
#define DEFAULT_RPC_PORT    8724
#define MESSAGE_HEADER_START_CHARS_MAINNET  \
    pchMessageStart[0] = 0xb1;              \
    pchMessageStart[1] = 0xb7;              \
    pchMessageStart[2] = 0x6d;              \
    pchMessageStart[3] = 0x44;
#define MESSAGE_HEADER_START_CHARS_TESTNET  \
    pchMessageStart[0] = 0xb2;              \
    pchMessageStart[1] = 0xb8;              \
    pchMessageStart[2] = 0x6e;              \
    pchMessageStart[3] = 0x45;
#define MESSAGE_HEADER_START_CHARS_REGTEST  \
    pchMessageStart[0] = 0xba;              \
    pchMessageStart[1] = 0xbf;              \
    pchMessageStart[2] = 0xb5;              \
    pchMessageStart[3] = 0xda;

//qt지갑에서 qr 코드 사용하는가?
#define TMI_USE_QRCODE 0

//블럭 해더 서명 크기
#define TMI_SIGN_BYTES 64

#endif //DEFINE_TMI_H
