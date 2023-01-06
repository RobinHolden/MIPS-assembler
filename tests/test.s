ADD $ra, $t0, $5
      ADDI $t0, $8, -0x156
AND $gp     , $t9, $15      
# Comment
BEQ     $1, $2, -10 # Comment
BGTZ    $1, 0x100
BLEZ    $1, 13
BNE     $1, $2, 10
DIV     $1, $2
J       0x100
JAL     150
JR      $1
LUI     $1, 10
LW      $1, 10, $2
MFHI    $1
MFLO    $1
MULT    $0, $1
OR      $0, $1, $2
ROTR    $0, $1, $2
SLL     $0, $1, $2
SLT     $0, $1, $2
SRL     $0, $1, $2
SUB     $0, $1, $2
SW      $0, 10, $1
XOR     $0, $1, $2

# EXPECTED_ASSEMBLY
# 0105f820
# 2107feaa
# 032fe024
# 1021fff6
# 1c200100
# 1820000d
# 1422000a
# 0022001a
# 08000100
# 0c000096
# 00200008
# 3c01000a
# 8c41000a
# 00000810
# 00000812
# 00010018
# 00220025
# 00210082
# 00010080
# 0022002a
# 00010082
# 00220022
# ac20000a
# 00220026

# EXPECTED_FINAL_STATE