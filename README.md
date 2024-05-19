# Encryption/Decryption Utility
## Overview
The program takes input from a text file, encrypts it, and writes the encrypted content to a new file with a .crp extension. Similarly, it can decrypt a .crp file and write the decrypted content to a new text file.

## Encryption
To encrypt a text file, use the -E flag followed by the name of the file to be encrypted. For example:
- ./file_encrypt_decrypt -E input.txt

## Decryption
To decrypt a .crp file, use the -D flag followed by the name of the file to be decrypted. For example:
- ./file_encrypt_decrypt -D input.crp

## Note
If no flag is specified, the program assumes encryption and encrypts the specified file by default.

## Algorithm
The encryption algorithm involves shifting ASCII values by a fixed amount and converting characters to hexadecimal format. Decryption reverses this process to recover the original text.
