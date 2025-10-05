#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TOPN 5

const char challenge_hex[] =
    "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

static char* xstrdup(const char* s) {
    size_t n = strlen(s) + 1;
    char* p = (char*)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

// heksamerkistä numeeriseksi
static int hex_nibble(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1; // ei ollut hexi
}

static unsigned char* hex_to_bytes(const char *hex, size_t *out_length)
{
    size_t n = strlen(hex);
    if (n % 2 != 0) {
        return NULL; // pariton hexi
    }

    unsigned char *buffer = (unsigned char *)malloc(n / 2);
    if (!buffer) {
        return NULL; // muisti 404
    }

    for (size_t i = 0; i < n; i += 2) {
        int high = hex_nibble(hex[i]);
        int low = hex_nibble(hex[i + 1]);

        if (high < 0 || low < 0) {
            free(buffer);
            return NULL; // hexivirhe
        }

        buffer[i / 2] = (unsigned char)((high << 4) | low); // yhdistä
    }

    *out_length = n / 2;
    return buffer;
}

// enkkupisteytys
static double english_scoring(const unsigned char *s, size_t n)
{
    const char *frequency = "etaoinshrdlcumwfgypbvkjxqzETAOINSHRDLCUMWFGYPBVKJXQZ"; // kiitos Robert Lewand
    double score = 0.0;

    for (size_t i = 0; i < n; i++) {
        unsigned char c = s[i];

        // pisteytyslogiikka joka toimii jos Omnissiah suo
        if (c == 0) {
            score -= 10.0; // nollatavu
        }

        if (isalpha(c)) {
            score += 3.0; // aakkonen
        }

        if (c == ' ') {
            score += 3.0; // välilyönti
        }

        if (strchr(frequency, c)) {
            score += 2.0; // yleinen kirjain
        }

        if (c == '.' || c == ',' || c == '-' || c == '!' || c == '?') {
            score += 0.5; // pisteet ja muita yleisiä merkkejä
        }

        if (c == '\t') {
            score -= 1.0; // tabulatuuri
        }

        if (c < 0x20 && c != '\n' && c != '\r' && c != '\t') {
            score -= 5.0; // kontrollimerkkejä
        }

        if (c > 0x7E) {
            score -= 5.0; // ASCII puuttuu
        }
    }

    // välilyöntien bonus
    size_t spaces = 0;
    for (size_t i = 0; i < n; i++) {
        if (s[i] == ' ') {
            spaces++;
            score += (double)spaces * 0.1;
        }
    }
    return score;
}

// onko ASCII
static int is_ascii(const unsigned char *s, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (!(s[i] == '\n' || s[i] == '\r' || s[i] == '\t' ||
              (s[i] >= 0x20 && s[i] <= 0x7E))) {
            return 0; // ei ole ASCII
        }
    }
    return 1; // on ASCII
}

static char* render_safe(const unsigned char *s, size_t n)
{
    char *out = (char*)malloc(n + 1);
    if (!out) return NULL;
    for (size_t i = 0; i < n; i++) {
        unsigned char c = s[i];
        out[i] = (isprint(c) || c == '\n' || c == '\r' || c == '\t') ? (char)c : '.';
    }
    out[n] = '\0';
    return out;
}

// rakenne TOP-listalle
struct Candidate {
    int key;
    double score;
    unsigned char *text;
};

// sorttaus TOP-listalle
static int cmp_candidates_desc(const void *a, const void *b)
{
    const struct Candidate *ca = (const struct Candidate*)a;
    const struct Candidate *cb = (const struct Candidate*)b;
    if (ca->score < cb->score) return 1;
    if (ca->score > cb->score) return -1;
    return 0;
}

// XOR ja kerää parhaat TOPN dekoodaukset
static void single_byte_xor_top(const unsigned char *input, size_t length,
                                int *out_key, unsigned char **out_decrypted,
                                struct Candidate top[TOPN])
{
    // alustetaan top
    for (int i = 0; i < TOPN; i++) {
        top[i].key = -1;
        top[i].score = -1e300;
        top[i].text = NULL;
    }

    unsigned char *tmp = (unsigned char *)malloc(length + 1);
    if (!tmp) { *out_key = -1; *out_decrypted = NULL; return; }

    for (int key = 0; key < 256; key++) {
        for (size_t i = 0; i < length; i++) {
            tmp[i] = input[i] ^ (unsigned char)key; // xorri
        }
        tmp[length] = '\0';

        double sc = english_scoring(tmp, length);

        // etsi huonoin topista
        int min_idx = 0;
        for (int i = 1; i < TOPN; i++) {
            if (top[i].score < top[min_idx].score)
                min_idx = i;
        }

        if (sc > top[min_idx].score) {
            unsigned char *copy = (unsigned char*)malloc(length + 1);
            if (!copy) continue;
            memcpy(copy, tmp, length + 1);
            if (top[min_idx].text) free(top[min_idx].text);
            top[min_idx].key = key;
            top[min_idx].score = sc;
            top[min_idx].text = copy;
        }
    }

    free(tmp);
    qsort(top, TOPN, sizeof(top[0]), cmp_candidates_desc);

    if (top[0].key >= 0) {
        *out_key = top[0].key;
        *out_decrypted = top[0].text;
    } else {
        *out_key = -1;
        *out_decrypted = NULL;
    }
}

int main(int argc, char **argv)
{
    char *hex_input = NULL;

    if (argc == 2 && strcmp(argv[1], "-") == 0) {
        // lue hex stdinistä
        size_t cap = 0, length = 0;
        int ch;

        while ((ch = fgetc(stdin)) != EOF) {
            if (ch == '\n' || ch == '\r') break;
            if (isspace(ch)) continue;
            if (cap == length) {
                size_t new_cap = cap ? cap * 2 : 256;
                char *p = (char *)realloc(hex_input, new_cap);
                if (!p) {
                    free(hex_input);
                    fprintf(stderr, "Muisti 404\n");
                    return 1;
                }
                hex_input = p;
                cap = new_cap;
            }
            hex_input[length++] = (char)ch;
        }

        if (!hex_input) {
            fprintf(stderr, "Ei syötettä\n");
            return 1;
        }

        if (cap == length) {
            char *p = (char *)realloc(hex_input, length + 1);
            if (!p) {
                free(hex_input);
                fprintf(stderr, "Muisti 404\n");
                return 1;
            }
            hex_input = p;
            cap = length + 1;
        }

        hex_input[length] = '\0';
    } else {
        hex_input = xstrdup(challenge_hex);
        if (!hex_input) {
            fprintf(stderr, "Ei koodia\n");
            return 1;
        }
    }

    // hexnäyttö
    printf("Hex: %s\n", hex_input);

    size_t in_length = 0;
    unsigned char *input_bytes = hex_to_bytes(hex_input, &in_length);

    if (!input_bytes) {
        fprintf(stderr, "Väärä hexi: %s\n", hex_input);
        free(hex_input);
        return 1;
    }

    int key = -1;
    unsigned char *decrypted = NULL;
    struct Candidate top[TOPN];

    single_byte_xor_top(input_bytes, in_length, &key, &decrypted, top);

    if (key < 0 || !decrypted) {
        fprintf(stderr, "Epäonnistui\n");
        free(input_bytes);
        free(hex_input);
        for (int i = 0; i < TOPN; i++) if (top[i].text) free(top[i].text);
        return 1;
    }

    // paras avain
    printf("Paras avain: %d (0x%02X", key, key);
    if (isprint(key)) {
        printf(", '%c')\n", key);
    } else {
        printf(", '.')\n");
    }

    // dekoodaus
    if (is_ascii(decrypted, in_length)) {
        printf("Dekoodattu: %s\n", decrypted);
    } else {
        char *safe = render_safe(decrypted, in_length);
        printf("Dekoodattu: %s\n", safe ? safe : "(virhe)");
        free(safe);
    }

    // TOP 5
    printf("\n-- TOP 5 --\n");
    for (int i = 0; i < TOPN; i++) {
        if (top[i].key < 0 || !top[i].text) continue;
        char *safe = render_safe(top[i].text, in_length);
        printf("%d) score=%.2f key=%d (0x%02X",
               i + 1, top[i].score, top[i].key, top[i].key);
        if (isprint(top[i].key)) printf(", '%c')\n", top[i].key);
        else printf(", '.')\n");
        printf("   %s\n", safe ? safe : "(virhe)");
        free(safe);
    }

    free(decrypted);
    for (int i = 0; i < TOPN; i++) if (top[i].text) free(top[i].text);
    free(input_bytes);
    free(hex_input);
    return 0;
}
