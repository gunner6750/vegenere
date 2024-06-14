// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
using namespace std;
string preprocess(string s){
    string res;
    for (int i=0;i<s.length();i++){
        if(s[i]<='z' && s[i]>='a'){
            res=res+s[i];
        }
    }
    return res;

}
string toLowerCase(string s){
    for (int i = 0; i < s.size(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}
string shift(string s,int num){

    for (int i=0;i<s.length();i++){
        s[i]=char(((s[i]-97)+num)%26+97);
    }
    return s;
}
void reset(int a[]){
    for (int i=0;i<26;i++){
        a[i]=i;
    }
}
int grading(string s){
    int res=0;
    for (int i=0;i<s.length();i++){
        if (s[i]=='e' or s[i]=='a' or s[i]=='i' or s[i]=='n' or s[i]=='t' or s[i]=='r' or s[i]=='s' or s[i]=='o')
        res++;
    }
    return res;
}
string fiveMostOccurence(string s){
    string res;
    int a[26];
    reset(a);
    for (char i=0;i<s.length();i++){
            a[s[i]-97]+=100;
        }
        sort(a,a+26,greater<int>());
        for (int i=0;i<5;i++){
            res+=char((a[i]%100)+97);
        }
        return res;
}
int bestShiftToLeft(string s){
    int maxGrad=-1;
    int res;
    for(int i=0;i<26;i++){
        if(maxGrad<grading(shift(s,26-i))){
            res=i;
            maxGrad=grading(shift(s,26-i));
            //cout<<shift(s,26-i)<<endl;
            //cout<<grading(shift(s,26-i));
        }
    }
    return res;
}
//decrypt message with a given key
string decriptE(string s,string key){
    string res;
    int ord[key.length()];
    for (int i=0;i<key.length();i++){
        ord[i]=key[i]-97;
    }
    int index=0;
    for (int i=0;i<s.length();i++){
        res=res+char((26+(s[i]-97)-ord[index])%26+97);
        index=(index+1)%4;
    }
    return res;
}
int main() {
    // Write C++ code here
    string s;
    cout<<"sample string: TKETOXSQSWOADRNMSOISHWRUSHJGSWOZTKEQDJEAFWHQVLLXAJEUTVTAOGOZIWSAWQAZDOOAKHDAUWOHEUANRRAPSSRQAGORWHSFCRUZTUYRAUMXAQDZOWADEPADKDBXEKOGSHBKAQYYEDNEIWWMSDBAUWTTIUTKYHADSRLPSTUMTWIEHVQGAUIEHPAPERFNRLCWAQDTAGFAUUWUNGOISVEFIQTTEIRANWORAVILEDNPPUOBOUTUOQWTIFHYOUEAROEESHXMCWLKFDIXEGTAPOEMSHTTEHYQTKEANOYBEUSANIODWKOYTKETOXSQWDSUNDNKWDYEPHCUAOWMSDRFHXRPEQTMNGTTAWWMSRNXYEEOAXSQIWHMPSEZEGTABHTTERNQHHLUVHDUNKETAGLUVHDUNLTROUANOXTFHUEQYHADSHVQRVIZCHHQHDDYOYEPOXTAFOOZDRNNEFAGSHIFMDDQHLMZEUVAUVAZDLRDIWANLHHQWDSMBRUFTKIDTBAEWHLXTDLXDDRWHDIDEGAZDQEHEUQGIWEMTHAEEZIFHKIYSHLRTKEFHLNSTKAFUVEPTRWARUYTIPMASWWMSWHQFDCFTKAFPHOBLHAXWDYEUVEPTRAEKKIYWKAFHHWMSOOAKLNSSRWARUIQDDBAUWHQWRRWEGIZLRCMLUAPIRWTIFHTEDLIABSGSHDFOWEXLKIEFUIQNGSIAVAXOWMARHIZTHRQSWIZGWHMNWHQYSRABDBXYWHAUJHFIWWMSWOAMRSFOIHUSIRUEQDEWRRWEGIZAGVQRWIEIQG"<<endl;
    cout << "input string: ";
    cin>>s;
    s=toLowerCase(s);

    int len=s.length();
    string subS[len-3];
    vector <string> v;
    string current="a";
    int icurr=0;
    int gcd=0;
    for (int i=0;i<len-3;i++){
        subS[i]=s.substr(i,3);
    }
    sort(subS, subS + len-3);
    for (int i=3;i<len-3;i++){
        if(subS[i]==subS[i-1] and subS[i-1]==subS[i-2] and subS[i-2]==subS[i-3] and current!=subS[i]){
            icurr=-1;
            current=subS[i];

            v.push_back(subS[i]);
            for(int i=0;i<len-3;i++){
                if(s.substr(i,3)==current){
                    if (icurr!=-1){
                    if (gcd==0){
                        gcd=i-icurr;
                    }

                    else gcd=__gcd(gcd,i-icurr);


                    }
                    icurr=i;
                }
            }
            //cout<<gcd;
        }

    }

    cout<<"recommend key length: "<<gcd<<endl;
    string partition[gcd];
    if (gcd<=1) return 0;
    int index=0;
    string finalkey;
    for (int i=0;i<s.length();i++){
        partition[index]=partition[index]+s[i];
        index=(index+1)%gcd;
    }

    for (int j=0;j<gcd;j++){
        index=bestShiftToLeft(fiveMostOccurence(partition[j]));
        //cout<<fiveMostOccurence(partition[j]);
        //cout<<index<<endl;
        finalkey=finalkey+char((index+1)%26+96);
    }
    cout<<"and the key is:"<<finalkey<<endl;
    cout<<"decripted message :"<<decriptE(s,finalkey);
}
