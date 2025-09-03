import base64

challenge_hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
challenge_base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

hex = input("Hex pls: ")
base64 = base64.b64encode(bytes.fromhex(hex)).decode('utf-8')
print("Base64: ", base64)

print("\n-- Tarkistus --")
if hex == challenge_hex and base64 == challenge_base64:
    print("Oikein!")
else:
    print("Väärin!")