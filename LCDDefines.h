
const byte digitShapes[] = {
  0<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 , // digit 0 
  0<<6 | 0<<5 | 0<<4 | 0<<3 | 1<<2 | 1<<1 | 0<<0 , // digit 1
  1<<6 | 0<<5 | 1<<4 | 1<<3 | 0<<2 | 1<<1 | 1<<0 , // digit 2
  1<<6 | 0<<5 | 0<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 , // digit 3
  1<<6 | 1<<5 | 0<<4 | 0<<3 | 1<<2 | 1<<1 | 0<<0 , // digit 4
  1<<6 | 1<<5 | 0<<4 | 1<<3 | 1<<2 | 0<<1 | 1<<0 , // digit 5
  1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 0<<1 | 1<<0 , // digit 6
  0<<6 | 0<<5 | 0<<4 | 0<<3 | 1<<2 | 1<<1 | 1<<0 , // digit 7
  1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 , // digit 8
  1<<6 | 1<<5 | 0<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 , // digit 9
};

const byte letterShapes[] = {
  1<<6 | 1<<5 | 1<<4 | 0<<3 | 1<<2 | 1<<1 | 1<<0 , // letter a
  1<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 0<<1 | 0<<0 , // letter b
  0<<6 | 1<<5 | 1<<4 | 1<<3 | 0<<2 | 0<<1 | 1<<0 , // letter c
  1<<6 | 0<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 0<<0 , // letter d
  1<<6 | 1<<5 | 1<<4 | 1<<3 | 0<<2 | 0<<1 | 1<<0 , // letter e
  1<<6 | 1<<5 | 1<<4 | 0<<3 | 0<<2 | 0<<1 | 1<<0 , // letter f
  0<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 0<<1 | 1<<0 , // letter g
  1<<6 | 1<<5 | 1<<4 | 0<<3 | 1<<2 | 0<<1 | 0<<0 , // letter h
  0<<6 | 0<<5 | 0<<4 | 0<<3 | 1<<2 | 1<<1 | 0<<0 , // letter i
  0<<6 | 0<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 , // letter j
  1<<6 | 1<<5 | 1<<4 | 0<<3 | 1<<2 | 0<<1 | 1<<0 , // letter k
  0<<6 | 1<<5 | 1<<4 | 1<<3 | 0<<2 | 0<<1 | 0<<0 , // letter l
  1<<6 | 0<<5 | 1<<4 | 0<<3 | 1<<2 | 0<<1 | 1<<0 , // letter m
  1<<6 | 0<<5 | 1<<4 | 0<<3 | 1<<2 | 0<<1 | 0<<0 , // letter n
  0<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 , // letter o
  1<<6 | 1<<5 | 1<<4 | 0<<3 | 0<<2 | 1<<1 | 1<<0 , // letter p
  1<<6 | 1<<5 | 0<<4 | 0<<3 | 1<<2 | 1<<1 | 1<<0 , // letter q
  0<<6 | 1<<5 | 1<<4 | 0<<3 | 0<<2 | 1<<1 | 1<<0 , // letter r
  1<<6 | 1<<5 | 0<<4 | 1<<3 | 1<<2 | 0<<1 | 1<<0 , // letter s
  0<<6 | 1<<5 | 1<<4 | 0<<3 | 0<<2 | 0<<1 | 1<<0 , // letter t
  0<<6 | 1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 0<<0 , // letter u
  1<<6 | 1<<5 | 1<<4 | 0<<3 | 0<<2 | 1<<1 | 0<<0 , // letter v
  1<<6 | 1<<5 | 0<<4 | 1<<3 | 0<<2 | 1<<1 | 0<<0 , // letter w
  1<<6 | 1<<5 | 1<<4 | 0<<3 | 1<<2 | 1<<1 | 0<<0 , // letter x
  1<<6 | 1<<5 | 0<<4 | 1<<3 | 1<<2 | 1<<1 | 0<<0 , // letter y
  1<<6 | 0<<5 | 1<<4 | 1<<3 | 0<<2 | 1<<1 | 1<<0 , // letter z 
};