#include <hip/hip_runtime.h>
#include <vector>
#include <iostream>
#include <array>

#define HIP_CHECK(condition)                                                                \
    {                                                                                       \
        const hipError_t error = condition;                                                 \
        if(error != hipSuccess)                                                             \
        {                                                                                   \
            std::cerr << "An error encountered: \"" << hipGetErrorString(error) << "\" at " \
                      << __FILE__ << ':' << __LINE__ << std::endl;                          \
            std::exit(1);                                                                   \
        }                                                                                   \
    }

struct Map {
    unsigned dst;
    unsigned src;
    unsigned size;
};

struct Range {
    unsigned start;
    unsigned size;
};

constexpr auto ranges = std::array{
    // Range{79, 14},
    // Range{55, 13},

    Range{3127166940U, 109160474U},
    Range{3265086325U, 86449584U},
    Range{1581539098U, 205205726U},
    Range{3646327835U, 184743451U},
    Range{2671979893U, 17148151U},
    Range{305618297U, 40401857U},
    Range{2462071712U, 203075200U},
    Range{358806266U, 131147346U},
    Range{1802185716U, 538526744U},
    Range{635790399U, 705979250U},
};

constexpr auto seed_to_soil = std::array{
    // Map{50, 98, 2},
    // Map{52U, 50U, 48U},

    Map{931304316U, 1786548802U, 232453384U},
    Map{3500539319U, 2322065235U, 6421609U},
    Map{496396007U, 147739714U, 266329192U},
    Map{3169724489U, 768672891U, 39526579U},
    Map{3689153715U, 1361862036U, 346985U},
    Map{1936948751U, 3328259881U, 542896984U},
    Map{3209251068U, 3154345676U, 173914205U},
    Map{1163757700U, 2814318523U, 24125066U},
    Map{2484210664U, 1362209021U, 231487475U},
    Map{3991904247U, 2133571422U, 188493813U},
    Map{1187882766U, 4045525873U, 83717994U},
    Map{861951350U, 3084992710U, 69352966U},
    Map{2715698139U, 2838443589U, 43714032U},
    Map{3830303258U, 4025104215U, 20421658U},
    Map{768672891U, 1268583577U, 93278459U},
    Map{4180398060U, 2019002186U, 114569236U},
    Map{3689500700U, 1593696496U, 10659519U},
    Map{1271600760U, 808199470U, 460384107U},
    Map{166497091U, 526585653U, 102729094U},
    Map{3700160219U, 3894961176U, 130143039U},
    Map{2966889400U, 2882157621U, 202835089U},
    Map{147739714U, 414068906U, 18757377U},
    Map{3850724916U, 4133608796U, 141179331U},
    Map{2759412171U, 2328486844U, 183672918U},
    Map{2479845735U, 4129243867U, 4364929U},
    Map{3480360150U, 4274788127U, 20179169U},
    Map{402636637U, 432826283U, 93759370U},
    Map{3383165273U, 2717123646U, 97194877U},
    Map{3506960928U, 1604356015U, 182192787U},
    Map{269226185U, 629314747U, 133410452U},
    Map{2943085089U, 3871156865U, 23804311U},
    Map{1731984867U, 2512159762U, 204963884U},
};

constexpr auto soil_to_fertilizer = std::array{
    // Map{0U, 15U, 37U},
    // Map{37U, 52U, 2U},
    // Map{39U, 0U, 15U},

    Map{3368312743U, 826425240U, 243745914U},
    Map{1045038113U, 3682756471U, 174490549U},
    Map{3931158487U, 1530223690U, 363808809U},
    Map{1219528662U, 2460222182U, 131099318U},
    Map{3020480207U, 1894032499U, 63879875U},
    Map{121779694U, 248970341U, 36319877U},
    Map{1993634034U, 2662348686U, 86667553U},
    Map{3612058657U, 1323325837U, 196530127U},
    Map{1531175223U, 2604354699U, 57993987U},
    Map{158099571U, 121779694U, 127190647U},
    Map{1867147432U, 3317666386U, 126486602U},
    Map{2080301587U, 2768963716U, 548702670U},
    Map{1402482267U, 1070171154U, 21180243U},
    Map{2959841028U, 4051272297U, 60639179U},
    Map{834756529U, 1966243663U, 128160296U},
    Map{3911211010U, 2749016239U, 19947477U},
    Map{962916825U, 3857247020U, 82121288U},
    Map{2629004257U, 3444152988U, 238603483U},
    Map{826425240U, 1957912374U, 8331289U},
    Map{1350627980U, 3939368308U, 51854287U},
    Map{1589169210U, 4214533702U, 80433594U},
    Map{2867607740U, 2094403959U, 92233288U},
    Map{1669602804U, 1125781209U, 197544628U},
    Map{3084360082U, 1519855964U, 10367726U},
    Map{1483712212U, 1091351397U, 34429812U},
    Map{3094727808U, 2186637247U, 273584935U},
    Map{1423662510U, 3991222595U, 60049702U},
    Map{3808588784U, 4111911476U, 102622226U},
    Map{1518142024U, 2591321500U, 13033199U},
};

constexpr auto fertilizer_to_water = std::array{
    // Map{49U, 53U, 8U},
    // Map{0U, 11U, 42U},
    // Map{42U, 0U, 7U},
    // Map{57U, 7U, 4U},

    Map{206818393U, 1973789958U, 18543481U},
    Map{2641351404U, 1992333439U, 41420268U},
    Map{58400970U, 2574944960U, 107826712U},
    Map{3710426911U, 4065366707U, 42793360U},
    Map{4217161704U, 4274048011U, 20919285U},
    Map{1926695368U, 705931711U, 328031436U},
    Map{1449580741U, 1210970895U, 50549447U},
    Map{907984567U, 1421828853U, 15115545U},
    Map{769748018U, 1108192216U, 102778679U},
    Map{451427938U, 35457870U, 38201654U},
    Map{2254726804U, 2033892789U, 137829519U},
    Map{923239194U, 1513967644U, 270588891U},
    Map{3753220271U, 4108160067U, 165887944U},
    Map{499804857U, 310274559U, 109862756U},
    Map{3061525238U, 3535532059U, 426476055U},
    Map{1193828085U, 73659524U, 196024324U},
    Map{872526697U, 0U, 35457870U},
    Map{1766386857U, 1261520342U, 160308511U},
    Map{4057593930U, 3283950856U, 159567774U},
    Map{1389852409U, 646203379U, 59728332U},
    Map{3919108215U, 3962008114U, 103358593U},
    Map{1577153434U, 1784556535U, 189233423U},
    Map{4022466808U, 3443518630U, 35127122U},
    Map{489629592U, 1098016951U, 10175265U},
    Map{923100112U, 2033753707U, 139082U},
    Map{2392556323U, 2390203683U, 158894869U},
    Map{1500130188U, 1436944398U, 77023246U},
    Map{2577297600U, 1033963147U, 64053804U},
    Map{609667613U, 2171722308U, 160080405U},
    Map{3488001293U, 3061525238U, 222425618U},
    Map{2551451192U, 2549098552U, 25846408U},
    Map{4238080989U, 3478645752U, 56886307U},
    Map{166227682U, 269683848U, 40590711U},
    Map{0U, 2331802713U, 58400970U},
    Map{225361874U, 420137315U, 226066064U},
};

constexpr auto water_to_light = std::array{
    // Map{88U, 18U, 7U},
    // Map{18U, 25U, 70U},

    Map{0U         , 1920724686U, 212138399U},
    Map{1038755613U, 1763451862U, 6623730U}  ,
    Map{1045379343U, 2396063798U, 245682603U},
    Map{1291061946U, 1770075592U, 150649094U},
    Map{1441711040U, 799272484U , 245821386U},
    Map{1687532426U, 1045093870U, 145711726U},
    Map{1833244152U, 0U         , 764535859U},
    Map{212138399U , 2132863085U, 224047237U},
    Map{2597780011U, 764535859U , 34736625U} ,
    Map{2632516636U, 1545176830U, 9229765U}  ,
    Map{2739726430U, 3712513349U, 582453947U},
    Map{3322180377U, 2914685303U, 488586806U},
    Map{3810767183U, 2778906155U, 135779148U},
    Map{3946546331U, 3589340640U, 8839399U}  ,
    Map{3955385730U, 2739726430U, 39179725U} ,
    Map{3994565455U, 3403272109U, 186068531U},
    Map{4180633986U, 3598180039U, 114333310U},
    Map{436185636U , 1481368346U, 9501316U}  ,
    Map{445686952U , 1600446740U, 163005122U},
    Map{608692074U , 1587251997U, 13194743U} ,
    Map{621886817U , 1190805596U, 46370961U} ,
    Map{668257778U , 1554406595U, 32845402U} ,
    Map{701103180U , 2356910322U, 39153476U} ,
    Map{740256656U , 1490869662U, 54307168U} ,
    Map{794563824U , 1237176557U, 244191789U},
};

constexpr auto light_to_temperature = std::array{
    // Map{45U, 77U, 23U},
    // Map{81U, 45U, 19U},
    // Map{68U, 64U, 13U},

    Map{432141642U, 1268486741U, 19474646U},
    Map{3617581823U, 3276436954U, 357008111U},
    Map{3505110084U, 3786131308U, 49942802U},
    Map{0U, 1287961387U, 432141642U},
    Map{3096011130U, 1808659179U, 409098954U},
    Map{1347993824U, 2675880000U, 161612192U},
    Map{3019335150U, 3199760974U, 76675980U},
    Map{3555052886U, 3137232037U, 62528937U},
    Map{2778092757U, 1720103029U, 88556150U},
    Map{451616288U, 2217758133U, 458121867U},
    Map{1509606016U, 0U, 1268486741U},
    Map{909738155U, 3836074110U, 138515824U},
    Map{1048253979U, 2837492192U, 299739845U},
    Map{2866648907U, 3633445065U, 152686243U},
};

constexpr auto temperature_to_humidity = std::array{
    // Map{0U, 69U, 1U},
    // Map{1U, 0U, 69U}

    Map{646729740U, 1519504972U, 559297346U},
    Map{1894539176U, 2990410634U, 44298872U},
    Map{232257988U, 972432123U, 414471752U},
    Map{2277879451U, 278205785U, 108711195U},
    Map{1775790220U, 132298732U, 118748956U},
    Map{3371687162U, 2663455233U, 326955401U},
    Map{1612056920U, 272509895U, 5695890U},
    Map{1208383109U, 3703499740U, 147415518U},
    Map{4070380190U, 4053129082U, 69974785U},
    Map{4155541210U, 3305585510U, 139426086U},
    Map{81956384U, 386916980U, 150301604U},
    Map{3987543096U, 896459472U, 75972651U},
    Map{2148980475U, 1386903875U, 128898976U},
    Map{1617752810U, 3445011596U, 154599732U},
    Map{4063515747U, 2078802318U, 6864443U},
    Map{2392568787U, 3599611328U, 101532389U},
    Map{2386590646U, 4123103867U, 5978141U},
    Map{2494101176U, 2122546980U, 187027686U},
    Map{2681128862U, 2085666761U, 36880219U},
    Map{4140354975U, 2648268998U, 15186235U},
    Map{1772352542U, 3051742077U, 3437678U},
    Map{1355798627U, 3850915258U, 202213824U},
    Map{3720104770U, 3055179755U, 250405755U},
    Map{3032992830U, 2309574666U, 338694332U},
    Map{1206027086U, 3701143717U, 2356023U},
    Map{1938838048U, 537218584U, 44257139U},
    Map{1558012451U, 81956384U, 50342348U},
    Map{3970510525U, 3034709506U, 17032571U},
    Map{1608354799U, 1515802851U, 3702121U},
    Map{1983095187U, 4129082008U, 165885288U},
    Map{3698642563U, 251047688U, 21462207U},
    Map{2718009081U, 581475723U, 314983749U},
};

constexpr auto humidity_to_location = std::array{
    // Map{60U, 56U, 37U},
    // Map{56U, 93U, 4U},

    Map{971626884U, 4275486551U, 19480745U},
    Map{1218249913U, 2090555906U, 502249162U},
    Map{2914848039U, 2902831882U, 224865747U},
    Map{3341591733U, 2819947352U, 82884530U},
    Map{991107629U, 2592805068U, 227142284U},
    Map{3424476263U, 606585628U, 95279547U},
    Map{4279176998U, 2064757318U, 10971709U},
    Map{3139713786U, 4068790015U, 201877947U},
    Map{606585628U, 701865175U, 365041256U},
    Map{3534582689U, 3291885426U, 744594309U},
    Map{1916997152U, 1066906431U, 997850887U},
    Map{1752809355U, 3127697629U, 164187797U},
    Map{1720499075U, 4036479735U, 32310280U},
    Map{4290148707U, 4270667962U, 4818589U},
    Map{3519755810U, 2075729027U, 14826879U},
};

template<size_t N>
__device__ unsigned int lookup(unsigned value, const std::array<Map, N>& maps) {
    bool found = false;
    for (const auto& map : maps) {
        if (!found && value >= map.src && value < (size_t) map.src + map.size) {
            value = value - map.src + map.dst;
            found = true;
        }
    }

    return value;
}

template<int block_size>
__global__ void fill_ranges(unsigned n, unsigned* block_counter, unsigned* global_min) {
    const unsigned lane_idx = threadIdx.x & (warpSize - 1);

    unsigned lowest = 0xFFFFFFFF;
    while (true) {
        unsigned i = 0;
        if (lane_idx == 0) {
            i = atomicAdd(block_counter, warpSize);
        }
        i = __builtin_amdgcn_readfirstlane(i) + lane_idx;

        if (i >= n)
            break;

        // Quickly search for the seed
        // The array is small anyway....
        unsigned x = 0;
        unsigned seed;
        for (const auto& r : ranges) {
            if (i >= x) {
                seed = r.start + i - x;
            }
            x += r.size;
        }

        unsigned location = seed;
        location = lookup(location, seed_to_soil);
        location = lookup(location, soil_to_fertilizer);
        location = lookup(location, fertilizer_to_water);
        location = lookup(location, water_to_light);
        location = lookup(location, light_to_temperature);
        location = lookup(location, temperature_to_humidity);
        location = lookup(location, humidity_to_location);

        lowest = location < lowest ? location : lowest;
    }

    for (int i = warpSize / 2; i > 0; i >>= 1) {
        const unsigned other = __shfl_xor(lowest, i, warpSize);
        lowest = other < lowest ? other : lowest;
    }

    if (lane_idx == 0) {
        atomicMin(global_min, lowest);
    }
}

int main() {
    unsigned total = 0;
    for (const auto& r : ranges) {
        total += r.size;
    }

    constexpr int block_size = 128;

    unsigned* d_counter;
    HIP_CHECK(hipMalloc(&d_counter, sizeof(unsigned)));
    HIP_CHECK(hipMemset(d_counter, 0, sizeof(unsigned)));

    unsigned* d_min;
    HIP_CHECK(hipMalloc(&d_min, sizeof(unsigned)));
    HIP_CHECK(hipMemset(d_min, 0xFF, sizeof(unsigned)));

    fill_ranges<block_size><<<
        dim3(120 * 10),
        dim3(block_size, 1, 1)
    >>>(total, d_counter, d_min);

    unsigned result;
    HIP_CHECK(hipMemcpy(&result, d_min, sizeof(unsigned), hipMemcpyDeviceToHost));
    std::cout << result << std::endl;

    HIP_CHECK(hipFree(d_min));
    HIP_CHECK(hipFree(d_counter));
}
