def hex_to_bytes(hex_str):
    if len(hex_str) % 2 != 0:
        return None
    try:
        return bytes.fromhex(hex_str)
    except ValueError:
        return None

# enkkupisteet
def score_english_text(text):
    frequency = "etaoinshrdlcumwfgypbvkjxqzETAOINSHRDLCUMWFGYPBVKJXQZ" # kiitos Robert Lewand jälleen kerran
    score = 0.0

    for c in text:
        if c == 0:
            score -= 10.0 # nollatavu
        if chr(c).isalpha():
            score += 3.0
        if c == ord(' '): # aakkonen
            score += 3.0
        if chr(c) in frequency: # välilyönti
            score += 2.0
        if chr(c) in '.,-!?': # yleinen kirjain
            score += 0.5
        if c == ord('\t'): # tabulatuuri
            score -= 1.0
        if c < 0x20 and c not in (ord('\n'), ord('\r'), ord('\t')): # kontrollimerkkejä
            score -= 5.0
        if c > 0x7E: # ASCII puuttuu
            score -= 5.0

    # välilyöntien bonus
    spaces = text.count(ord(' '))
    score += spaces * 0.1
    return score

def single_byte_xor_decrypt(ciphertext):
    best_score = float('-inf')
    best_text = None
    best_key = None

    for key in range(256):
        decrypted = bytes(c ^ key for c in ciphertext)
        score = score_english_text(decrypted)
        if score > best_score:
            best_score = score
            best_text = decrypted
            best_key = key

    return best_key, best_text, best_score

def find_encrypted_line(filename):
    best_score = float('-inf')
    best_line_no = -1
    best_decrypted = None
    best_key = -1

    try:
        with open(filename, 'r') as file:
            for line_no, line in enumerate(file, 1):
                line = line.strip()
                if not line or len(line) != 60:
                    continue

                ciphertext = hex_to_bytes(line)
                if not ciphertext:
                    continue

                key, decrypted, score = single_byte_xor_decrypt(ciphertext)
                if score > best_score:
                    best_score = score
                    best_decrypted = decrypted
                    best_key = key
                    best_line_no = line_no

    except FileNotFoundError:
        print(f"Virhe: Tiedostoa '{filename}' ei löydy")
        return None, None, None
    except Exception as e:
        print(f"Virhe lukiessa: {e}")
        return None, None, None

    return best_line_no, best_decrypted, best_key

def main():
    filename = "4.txt"
    line_no, decrypted, key = find_encrypted_line(filename)

    if line_no is None or decrypted is None or key is None:
        print("Ei löydy kyllä mitään")
        return

    print(f"Paras rivi: {line_no}")
    print(f"Paras avain: {key} (0x{key:02X})")
    try:
        decrypted_text = decrypted.decode('ascii')
        print(f"Tulos: {decrypted_text}")
    except UnicodeDecodeError:
        safe_text = ''.join(chr(c) if 32 <= c <= 126 or c in (10, 13, 9) else '.' for c in decrypted)
        print(f"Tulos: {safe_text}")

if __name__ == "__main__":
    main()