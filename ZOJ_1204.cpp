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
            //��һ��ѭ��ȷ����ʽ����м�����
            for(int l=2; l<=lenSize; l++)
            {
                set<int>::iterator secondIter=numberSet.begin();
                set<int>::iterator secondEndIter=numberSet.end();
                for(int j=0; j<l-1; j++)
                    secondEndIter--;
                //�ڶ���ѭ��ȷ����ʽ��ߵ�һ��ֵ
                for(secondIter; secondIter!=secondEndIter; secondIter++)
                {
                    int leftFirst=*secondIter;
                    set<int>::iterator thirdIter=secondIter;
                    thirdIter++;
                    set<int>::iterator thirEndIter=secondEndIter;
                    thirEndIter++;
                    //������ѭ��ȷ����ʽ��ߵڶ���ֵ
                    for(thirdIter; thirdIter!=thirEndIter; thirdIter++)
                    {
                        int leftSecond=*thirdIter;
                        //�����ߵ�һ��ֵ����ߵڶ�ֵ�����ʽ
                        vector<int> Equation;
                        Equation.push_back(leftFirst);
                        Equation.push_back(leftSecond);
                        //�����Ѿ�����������ֵ��������ߵ�ʽ��Ԫ�ظ���Ϊ2
                        int leftSize=2;
                        set<int>::iterator forthIter=thirdIter;
                        //��ߵ�ʽ�ĺ�
                        int sum=leftFirst+leftSecond;
                        //���Ĵ�ѭ��ȡʣ��l-2��ֵ�������
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
                        //�����ѭ���ж��Ƿ���ֵ����ߵ�ʽ�ĺ����
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




