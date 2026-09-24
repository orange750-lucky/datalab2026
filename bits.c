/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~ (~x |~y );
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^(XOR) && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x && !y)
        return 1;

    if (!x)
        return 0;

    if (!y)
        return 0;

    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int ans=0;
    int s=0;

    s=(v>0xFFFF)<<4;
    ans=ans|s;
    v=v>>s;

    s=(v>0xFF)<<3;
    ans=ans|s;
    v=v>>s;

    s=(v>0xF)<<2;
    ans=ans|s;
    v=v>>s;

    s=(v>0x3)<<1;
    ans=ans|s;
    v=v>>s;

    s=v>0x1;
    ans=ans|s;

    return ans;
}


/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int a=0,b=0,temp=0;
    n =n<<3;
    m =m<<3;
    a = (x >> n) & 0xFF;
    b = (x >> m) & 0xFF;
    int temp1=0xFF<<n;
    int temp2=0xFF<<m;
    temp = ~(temp |(temp1 | temp2));
    temp = temp &x;
    a =a<<m;
    b =b<<n;
    temp = temp | (a | b);

    return temp;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned ans=0;
    int i =32;
    
    while(i){
        ans =ans<<1;
        ans =ans | (v & 1);
        v =v>>1;
        i=i-1;
    }

    return ans;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int a;
    int mask;
    int ans;

    a = 1 << 31;
    a = a >> n;
    a = a << 1;
    mask = ~a;

    ans = x >> n;
    ans = ans & mask;

    return ans;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count=0;
    int s=0;
    s=!((~x)& 0xFFFF0000)<<4;
    count=count+s;
    x=x<<s;
    s=!((~x)& 0xFF000000)<<3;
    count=count+s;
    x=x<<s;
    s=!((~x)& 0xF0000000)<<2;
    count=count+s;
    x=x<<s;
    s=!((~x)& 0xc0000000)<<1;
    count=count+s;
    x=x<<s;
    s=!((~x)& 0x80000000);
    count=count+s;
    x = x << s;  
    count = count + ((x >> 31) & 1);
    return count;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ans;
    unsigned y;
    unsigned f;
    unsigned r;
    int e=158;//127+31

    if(!x)
        return 0;

    ans=x&0x80000000;
    y=x;

    if(ans)
        y=~y+1;

    while(!(y&0x80000000)){
        y=y<<1;
        e=e-1;
    }

    f=y>>8;
    r=y&0xFF;

    if(r>0x80)
        f=f+1;
    else if(r==0x80){
        if(f&1)
            f=f+1;
    }

    if(f>>24){
        e=e+1;
        f=f>>1;
    }

    f=f&0x7FFFFF;
    ans=ans|(e<<23)|f;

    return ans;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
   unsigned x=uf>>23;
   x=x&255;
   
   if(x==255)return uf;
   unsigned ans=uf<<9;
    
   if(x==0){
        if(ans & 0x80000000){
            x+=1;
            }
        ans=ans<<1;
    }
    else x+=1;

    ans=ans>>9;
    
    unsigned s=uf&0x80000000;

    x=x<<23;
    ans=s|x|ans;

    return ans;

}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int f=uf2 & 0x80000000;
    int e=uf2<<1 >>21;
    unsigned temp=uf2<<12 >>12;
    unsigned ans;

    e=e-1023;

    if(e<0)
        return 0;

    if(e>31)
        return 0x80000000;

    temp=temp|0x100000;

    if(e<=20){
        ans=temp>>(20-e);
    }
    else{
        ans=temp<<(e-20);
        ans=ans|(uf1>>(52-e));
    }

    if(!f){
        if(ans>0x7fffffff)
            return 0x80000000;
    }
    else{
        if(ans>0x80000000)
            return 0x80000000;
        ans=-ans;
    }

    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127){
        return 0x7F800000;
    }
    else if(x>=-126){
        return (x+127)<<23;
    }
    else if(x>=-149){
        return 1<<(x+149);
    }
    else{
        return 0;
    }
}
