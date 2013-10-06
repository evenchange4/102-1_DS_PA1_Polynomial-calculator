#include "Polynomial.h"   // header file
#include <iostream>
#include <cstdlib>
#include <fstream> // for file I/O 

using namespace std;

int main(int argc, char *argv[])
{   
    // ################### file IO ###################
    ifstream fin;  // for reading file 
    ofstream fout; // for writing file 
    string temp; 
    
    // argv[0] 為程式路徑，所以要讀第二個參數，也就是 argv[1]。
    if (argc == 2){  
        // 開檔 input1.txt
        fin.open(argv[1]);
    }
    // 如果沒有在 command line 輸入參數，則從程式裡面輸入。
    else{ 
        cout << "Please input file name: ";
        cin >> temp;
        // 開檔 input1.txt
        fin.open(temp.c_str()); // c_str() : string to char string
    }
    
    //­ 若開檔 input1.txt 失敗，可能是檔案不存在。
    if (fin.fail()){ 
        cout << "Fail to open file\n";
        exit(1); // 非正常結束程式
    } 

    // 建新檔 output1.txt，預設為覆蓋。
    string output_fileName = "output";
    output_fileName = output_fileName + argv[1][5] + ".txt";
    fout.open(output_fileName.c_str()); 

    //­ 若開檔 output1.txt 失敗
    if (fout.fail()){ 
        cout << "Fail to open file\n";
        exit(1); // 非正常結束程式
    }

    // ################### file parse ###################
    char m;
    char cur_operator, next_operator;
    int a, b;
    int polyNumber = 1;
    Polynomial polyResult;
    // string operator = "+";
    
    while (!fin.eof()){  //­ not End-of-file，尚未讀到結尾。
        Polynomial poly;

        // set each Polynomial block
        while(true){
            fin >> a >> b;  // '>>' 等同 get()，character by character
            poly.set(b, a); // Polynomial set()
            fin.get();      // 把換行符號吃掉。
            m = fin.get();  // 嘗試吃一個 character

            // 如果 m 是 operator 
            if( m == '+' || m == '*'){
                next_operator = m;
                break;
            }
            else if( m == EOF ){ // end-of-file
                break;
            }
            else{
                fin.putback(m);  // 呃，吃錯了，吐回去。
            }
        }

        //print every poly 寫進 output file
        fout << "Polynomial " << polyNumber << ":" << poly.getPoly() << endl;    
        fout << "Degree:"<< poly.getDegree() << endl;
        fout << "# of nonzero var: " << poly.getNonZero() << endl<< endl;

        if( polyNumber == 1 ){ 
            polyResult.add(poly);
        }
        else if( cur_operator == '+'){
            polyResult.add(poly);
        }
        else if( cur_operator == '*'){
            polyResult.multiplies(poly);
        }
        cur_operator = next_operator; 
        polyNumber++;
    } 
    //printPolyResult
    fout << "Result Polynomial:" << polyResult.getPoly() << endl;    
    fout << "Degree:"<< polyResult.getDegree() << endl;
    fout << "# of nonzero var: " << polyResult.getNonZero();

    // file close
    fin.close();
    fout.close(); 
}