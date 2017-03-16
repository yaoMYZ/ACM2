#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;


void showEquation(vector<int> Equation,int rightNum)
{
    printf("%d",Equation[0]);
    for(int k=1; k<Equation.size(); k++)
    {
        printf("+%d",Equation[k]);
    }
    printf("=%d\n",rightNum);
}

int main()
{

    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        int m=0;
        scanf("%d",&m);
        bool ifHaveEqu=false;
        set<int> numberSet;
        int inputNum=0;
        if(m<=2)
        {
            for(int j=0; j<m; j++)
            {
                scanf("%d",&inputNum);
            }
        }
        else
        {
            for(int j=0; j<m; j++)
            {
                scanf("%d",&inputNum);
                numberSet.insert(inputNum);
            }
            int lenSize=numberSet.size()-1;
            //第一个循环确定等式左边有几个数
            for(int l=2; l<=lenSize; l++)
            {
                set<int>::iterator secondIter=numberSet.begin();
                set<int>::iterator secondEndIter=numberSet.end();
                for(int j=0; j<l-1; j++)
                    secondEndIter--;
                //第二个循环确定等式左边第一个值
                for(secondIter; secondIter!=secondEndIter; secondIter++)
                {
                    int leftFirst=*secondIter;
                    set<int>::iterator thirdIter=secondIter;
                    thirdIter++;
                    set<int>::iterator thirEndIter=secondEndIter;
                    thirEndIter++;
                    //第三个循环确定等式左边第二个值
                    for(thirdIter; thirdIter!=thirEndIter; thirdIter++)
                    {
                        int leftSecond=*thirdIter;
                        //把作边第一个值和左边第二值加入等式
                        vector<int> Equation;
                        Equation.push_back(leftFirst);
                        Equation.push_back(leftSecond);
                        //由于已经加入了两个值，所以左边等式的元素个数为2
                        int leftSize=2;
                        set<int>::iterator forthIter=thirdIter;
                        //左边等式的和
                        int sum=leftFirst+leftSecond;
                        //第四次循环取剩下l-2个值进行组合
                        while(leftSize<l)
                        {
                            forthIter++;
                            int newNum=*forthIter;
                            sum+=newNum;
                            Equation.push_back(newNum);
                            leftSize++;
                        }
                        set<int>::iterator fithIter=forthIter;
                        fithIter++;
                        //第五次循环判断是否有值与左边等式的和相等
                        for(fithIter; fithIter!=numberSet.end(); fithIter++)
                        {
                            int rightNum=*fithIter;
                            if(sum==rightNum)
                            {
                                ifHaveEqu=true;
                                showEquation(Equation,rightNum);
                                break;
                            }
                            if(sum<rightNum)
                            {
                                break;
                            }
                        }
                        Equation.clear();
                    }
                }
            }

        }
        if(!ifHaveEqu)
            printf("Can't find any equations.\n");
    }
    return 0;
}




