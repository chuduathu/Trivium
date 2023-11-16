#include <iostream>
#include <bitset>
const uint8_t secret_state = 288;

using namespace std;

void trivium(uint8_t K[], uint8_t IV[]) {
    bitset<secret_state> s;
    bitset<secret_state> t1, t2, t3;

    for (int i = 0; i < 80; ++i) {
        s[i] = K[i];
    }
    for (int i = 0; i < 80; ++i) {
        s[93 + i] = IV[i];
    }
    s[287] = 1;
    s[286] = 1;
    s[285] = 1;

    bool init_done = false;
    for (int i = 0; i < 1152; ++i) {
        t1 = s[65] ^ (s[90] & s[91]) ^ s[92] ^ s[170];
        t2 = s[161] ^ (s[174] & s[175]) ^ s[176] ^ s[263];
        t3 = s[242] ^ (s[285] & s[286]) ^ s[287] ^ s[68];

        s >>= 1;

       s[0] = t3[0];
        s[93] = t1[0];
        s[177] = t2[0];
    }
    init_done = true;
    cout << "Initialization Done" << endl;

    if (init_done) {
        while (init_done) {
            t1 = s[65] ^ s[92];
            t2 = s[161] ^ s[176];
            t3 = s[242] ^ s[287];

            bitset<288> output_bit = (t1 ^ t2 ^ t3);
            t1 = s[65] ^ (s[90] & s[91]) ^ s[92] ^ s[170];
            t2 = s[161] ^ (s[174] & s[175]) ^ s[176] ^ s[263];
            t3 = s[242] ^ (s[285] & s[286]) ^ s[287] ^ s[68];

            s >>= 1;
            s[0] = t3[0];
            s[93] = t1[0];
            s[177] = t2[0];

            cout << "output bit " << output_bit << endl;
        }
    }
}

int main() {
    uint8_t K[80]; 
    uint8_t IV[80];

    trivium(K, IV);

    return 0;
}