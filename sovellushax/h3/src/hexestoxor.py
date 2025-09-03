
challenge_hex_1 = "1c0111001f010100061a024b53535009181c"
challenge_hex_2 = "686974207468652062756c6c277320657965"
challenge_result = "746865206b696420646f6e277420706c6179"

hex_1 = input("Hex 1 pls: ")
hex_2 = input("Hex 2 pls: ")

def xor(buffer_1, buffer_2):
    return bytes(a ^ b for a, b in zip(buffer_1, buffer_2))

bytes_1 = bytes.fromhex(hex_1)
bytes_2 = bytes.fromhex(hex_2)
result = xor(bytes_1, bytes_2).hex()

print("XOR: ", result)

print("\n-- Kovakoodin Tarkistus --")
if hex_1 == challenge_hex_1 and hex_2 == challenge_hex_2 and result == challenge_result:
    print("Oikein!")
else:
    print("Väärin!")