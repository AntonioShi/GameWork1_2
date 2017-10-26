//竞赛编程作业1-2完成
/*
 * 问题二：高精度加法运算
问题描述
输入两个整数a和b，输出这两个整数的和。a和b都不超过100位。
算法描述
由于a和b都比较大，所以不能直接使用语言中的标准数据类型来存储。对于这种问题，一般使用数组来处理。
定义一个数组A，A[0]用于存储a的个位，A[1]用于存储a的十位，依此类推。同样可以用一个数组B来存储b。
计算c = a + b的时候，首先将A[0]与B[0]相加，如果有进位产生，则把进位（即和的十位数）存入r，把和的个位数存入C[0]，即C[0]等于(A[0]+B[0])%10。
 然后计算A[1]与B[1]相加，这时还应将低位进上来的值r也加起来，即C[1]应该是A[1]、B[1]和r三个数的和．
 如果又有进位产生，则仍可将新的进位存入到r中，和的个位存到C[1]中。依此类推，即可求出C的所有位。
最后将C输出即可。
输入格式
输入包括两行，第一行为一个非负整数a，第二行为一个非负整数b。两个整数都不超过100位，两数的最高位都不是0。
输出格式
输出一行，表示a + b的值。
样例输入
20100122201001221234567890
2010012220100122
样例输出
20100122203011233454668012
 */
#include <iostream>
using namespace std ;

void Input(int *len, int a[], string st){

    cin >> st ;
    if(st.length() > 400){
        cout << "输入过长,请重新输入!" << endl ;
        cin >> st ;
    }

    *len = st.length() ;//7
    for (int i = 0; i < (*len); i++) {
//        a[i] = (st[(*len) -1 - i] - 48) ;//为了后面运算方便,这里采用倒序的方式存放,确保0号元素为个位数的数字
        a[i] = (st[i] - 48) ;
    }

}

void Output(int a[], int len){

    for (int i = len-1; i >= 0; i--) {
        cout << a[i] << " " ;
    }
    cout << endl ;
}

//高精度的计算
void Highpricise(int a[], int b[], int c[], int *clen){
    int temp = 0 ;

    for (int i = 0; i < *clen; i++) {

        c[i] = (a[i] + b[i]) % 10 + temp ;

        if(a[i] + b[i] >= 10){
            temp = 1;//保存进位
        }
        else{
            temp = 0 ;
        }

        if(a[*clen-1] + b[*clen-1] >= 10){
          c[i+1] = temp ;
            (*clen)++ ;
        }
    }

    //还有一个进位的问题没有解决

}

void MakeZero(int a[], int *len, int max){//在len到max之间补位0
    //int size = max - len ;
    for (int i = (*len); i < max; i++) {
        a[i] = 0 ;//先给空位补0
    }

    int temp = 0 ;
    for (int i = *len-1, j = 0; i >= 0; i--, j++) {//换位,把非零数字调换到低位,把补上来的0调换到高位,保持数值不变
        temp = a[max - 1 - j] ;
        a[max - 1 - j] = a[i] ;
        a[i] = temp ;
    }

        *len = max ;

}

void Reverse(int a[], int len){
    int temp ;

    for (int i = 0; i < len/2; i++) {
        temp = a[len-1-i] ;
        a[len-1-i] = a[i] ;
        a[i] = temp ;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int a[100], b[100], c[100] ;

    int alen, blen, clen ;
    string st ;

    //输入
    Input(&alen, a, st) ;
    Input(&blen, b, st) ;

    //运算之间的准备阶段--补位
    if(alen > blen){
        clen = alen ;
        MakeZero(b, &blen, alen) ;

    }
    else if(alen < blen){
        clen = blen ;
        MakeZero(a, &alen, blen) ;
    }
    else{
        clen = blen ;
    }

    Reverse(a, alen) ;
    Reverse(b, blen) ;
    //运算
    Highpricise(a, b, c, &clen) ;

    //显示
    //Output(a, alen) ;
    //Output(b, blen) ;
    Output(c, clen) ;

    return 0;
}