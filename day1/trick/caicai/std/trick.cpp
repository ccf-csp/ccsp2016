#include <iostream>
using namespace std;
#include <string>

#define MAXN 1010
#define MAX_MEMORY 32768
#define TIME_LIMIT 1000000
#define LEN_LIMIT 100

struct oper{
    string str; //��Ų��������ַ�����ʽ
    int kind;   //���������࣬��1..4��ʶ
    /*
        1 02C0  ������
        2 AX    �Ĵ���
        3 T02C0 �ڴ�+������
        4 TAX   �ڴ�+�Ĵ���
    */
    unsigned short value;
    /*
        ���������洢��������ֵ
        �Ĵ�������0..3��ʶAX..DX
        �ڴ�+���������洢��������ֵ
        �ڴ�+�Ĵ�������0..3��ʶTAX..TDX
    */
    bool check()    //���ò�������ʽ�Ƿ���ȷ��������str��kind��value���г�ʼ��
    {
        int len = str.length();
        if(len==2)
        {
            value = 4;
            if(str == "AX") value = 0;
            if(str == "BX") value = 1;
            if(str == "CX") value = 2;
            if(str == "DX") value = 3;
            if(value == 4) return false;
            kind = 2;
            return true;
        }
        if(len==3)
        {
            value = 4;
            if(str == "TAX") value = 0;
            if(str == "TBX") value = 1;
            if(str == "TCX") value = 2;
            if(str == "TDX") value = 3;
            if(value == 4) return false;
            kind = 4;
            return true;
        }
        if(len < 4 || len > 5) return false;
        int base = 0;
        if(str[0] == 'T') base = 1;
        if(len == base + 4)
        {
            value = 0;
            for(int i=0; i<4; i++)
            {
                char ch = str[base+i];
                unsigned short digit;
                if(ch >= '0' && ch <= '9')
                {
                    digit = ch - '0';
                }
                else if(ch >= 'A' && ch <= 'F')
                {
                    digit = ch - 'A' + 10;
                }
                else return false;
                value = value * 16 + digit;
            }
            if(base == 0) kind = 1;
            else kind = 3;
            return true;
        }
        else return false;
    }
};

struct instruction{
    string name;    //���ָ���ײ����ַ�����ʽ
    int kind;       //1..7�ֱ��ӦRUN��CMP��80..86��ӦJMP��JNE
    oper op1,op2;   //����������
    bool check()    //����ָ���ʽ�Ƿ���ȷ��������name��ʼ��kind���������������
    {
        if(name == "RUN")
        {
            kind = 1;
            return true;
        }
        if(name == "STOP")
        {
            kind = 2;
            return true;
        }
        if(name == "ECHO")
        {
            kind = 3;
            cin >> op1.str;
            return op1.check();
        }
        if(name == "ADD")
        {
            kind = 4;
            cin >> op1.str >> op2.str;
            return op1.check() && (op1.kind != 1) && op2.check() && (op1.kind < 3 || op2.kind < 3);
        }
        if(name == "INC")
        {
            kind = 5;
            cin >> op1.str;
            return op1.check() && (op1.kind != 1);
        }
        if(name == "MOV")
        {
            kind = 6;
            cin >> op1.str >> op2.str;
            return op1.check() && (op1.kind != 1) && op2.check() && (op1.kind < 3 || op2.kind < 3);
        }
        if(name == "CMP")
        {
            kind = 7;
            cin >> op1.str >> op2.str;
            return op1.check() && op2.check() && (op1.kind < 3 || op2.kind < 3);
        }
        if(name == "JMP")
        {
            kind = 80;
            cin >> op1.str;
            return op1.check();
        }
        if(name == "JG")
        {
            kind = 81;
            cin >> op1.str;
            return op1.check();
        }
        if(name == "JL")
        {
            kind = 82;
            cin >> op1.str;
            return op1.check();
        }
        if(name == "JE")
        {
            kind = 83;
            cin >> op1.str;
            return op1.check();
        }
        if(name == "JNG")
        {
            kind = 84;
            cin >> op1.str;
            return op1.check();
        }
        if(name == "JNL")
        {
            kind = 85;
            cin >> op1.str;
            return op1.check();
        }
        if(name == "JNE")
        {
            kind = 86;
            cin >> op1.str;
            return op1.check();
        }
        return false;
    }
};

instruction code[MAXN]; // �������ָ��
unsigned short memory[MAX_MEMORY];  // [3000,B000) �ڴ����ݶΣ���ʹ�õ�8λ����unsigned short������Ϊ�˴�����
unsigned short reg[4];  // �Ĵ��� 0 AX  1 BX  2 CX  3 DX
bool cmp = false;       // ִ�й�CMPָ�����ΪTrue
unsigned short aa,bb;   // ���CMPָ�������������е�ֵ
int nnow = 0;

bool read_data(oper op,unsigned short &data)    // ��ȡ������op�е�ֵ������data
{
    if(op.kind == 1)
    {
        data = op.value;
        return true;
    }
    if(op.kind == 2)
    {
        data = reg[op.value];
        return true;
    }
    if(op.kind == 3)
    {
        if(op.value < 12288 || op.value >= 45056 - 1)
        {
            cout << "ACCESS_VIOLATION" << endl;
            return false;
        }
        unsigned short tmp = op.value - 12288;
        data = memory[tmp] + memory[tmp+1] * 256;
        return true;
    }
    if(op.kind == 4)
    {
        unsigned short tmp = reg[op.value];
        if(tmp < 12288 || tmp >= 45056 - 1)
        {
            cout << "ACCESS_VIOLATION" << endl;
            //cout << "at line " << nnow << endl;
            return false;
        }
        tmp -= 12288;
        data = memory[tmp] + memory[tmp+1] * 256;
        return true;
    }
    cerr << "PE - Wrong Operator" << endl;
    return false;
}

bool write_data(oper op,unsigned short data)    // ��������op�е�ֵ�޸�Ϊdata
{
    if(op.kind == 2)
    {
        reg[op.value] = data;
        return true;
    }
    if(op.kind == 3)
    {
        if(op.value < 12288 || op.value >= 45056 - 1)
        {
            cout << "ACCESS_VIOLATION" << endl;
            return false;
        }
        unsigned short tmp = op.value - 12288;
        memory[tmp] = data & 255;
        memory[tmp+1] = data >> 8;
        return true;
    }
    if(op.kind == 4)
    {
        unsigned short tmp = reg[op.value];
        if(tmp < 12288 || tmp >= 45056 - 1)
        {
            cout << "ACCESS_VIOLATION" << endl;
            //cout << "at line " << nnow << endl;
            return false;
        }
        tmp -= 12288;
        memory[tmp] = data & 255;
        memory[tmp+1] = data >> 8;
        return true;
    }
    cerr << "PE - Wrong Operator" << endl;
    return false;
}

void output(unsigned short data)    // ����λʮ�����Ƹ�ʽ���data
{
    unsigned short tmp;
    char ch[4];
    for(int i=0; i<4; i++)
    {
        tmp = data & 15;
        data = data >> 4;
        if(tmp<10) ch[i] = '0' + tmp;
        else ch[i] = 'A' + tmp - 10;
    }
    for(int i=3; i>=0; i--)
        cout << ch[i];
    cout << endl;
}

bool work()
{
    //�ȼ���ʽ����
    int n = 0;  //ָ����������code[1]��ʼ���ָ��
    while(cin >> code[n+1].name)
    {
        n++;
        if(code[n].check() == false)
        {
            cerr << "PE at " << n << " line" << endl;
            return false;
        }
        //cerr << code[n].op1.kind << "\t" << code[n].op1.value << "\t" << code[n].op2.kind << "\t" << code[n].op2.value << endl;
        if(n == LEN_LIMIT) break;   // ����LEN_LIMIT��ָ����Զ��˳�
    }
    if(code[n].kind != 2 || code[1].kind != 1)  // ����һ�������һ��ָ���Ƿ�ΪRUN��STOP
    {
        cerr << "PE at 1 or " << n << " line" << endl;
        return false;;
    }
    for(int i=2; i<n; i++)  // ����Ƿ��ж����RUN��STOP
        if(code[i].kind < 3)
    {
        cerr << "PE at " << i << " line" << endl;
        return false;
    }
    // ��ʱ��֤��ʽ��ȷ
    int cnt = 0;
    unsigned short next = 2, i = 1;
    unsigned short a,b,x;
    bool ok = false;    // okΪTRUE��ʾ����ͨ��STOP��������
    cmp = false;
    while(true)
    {
        nnow = i;
        int kind = code[i].kind;
        if(kind == 2)   // STOP
        {
            ok = true;
            break;
        }
        if(kind == 3)   // ECHO A
        {
            if(read_data(code[i].op1, a)) output(a);
            else break;
        }
        if(kind == 4)   // ADD A B
        {
            if(!read_data(code[i].op1, a)) break;
            if(!read_data(code[i].op2, b)) break;
            a += b;
            if(!write_data(code[i].op1, a)) break;
        }
        if(kind == 5)  // INC A
        {
            if(!read_data(code[i].op1, a)) break;
            a++;
            if(!write_data(code[i].op1, a)) break;
        }
        if(kind == 6)   // MOV A B
        {
            if(!read_data(code[i].op2, b)) break;
            if(!write_data(code[i].op1, b)) break;
        }
        if(kind == 7)   // CMP A B
        {
            if(!read_data(code[i].op1, aa)) break;
            if(!read_data(code[i].op2, bb)) break;
            cmp = true;
        }
        if(kind >= 80)  // JMP X
        {
            if(kind > 80 && !cmp)
            {
                cout << "CMP_MISSING" << endl;
                break;
            }
            if(!read_data(code[i].op1, x)) break;
            bool flag = false;
            if(kind == 80) flag = true;
            if(kind == 81 && aa > bb) flag = true;
            if(kind == 82 && aa < bb) flag = true;
            if(kind == 83 && aa == bb) flag = true;
            if(kind == 84 && aa <= bb) flag = true;
            if(kind == 85 && aa >= bb) flag = true;
            if(kind == 86 && aa != bb) flag = true;
            if(flag)
            {
                if(x<2 || x>n)
                {
                    cout << "RUNTIME_ERROR" << endl;
                    break;
                }
                next = x;
            }
        }
        cnt++;
        if(cnt == TIME_LIMIT)
        {
            if(code[i].kind != 2) cout << "TLE" << endl;
            break;
        }
        i = next;
        next = i + 1;
    }
    return ok;
}


int main()
{
    work();
    return 0;
}
