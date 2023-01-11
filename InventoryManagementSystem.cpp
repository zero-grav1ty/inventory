#include<bits/stdc++.h>
using namespace std;

//global variables
string orderFrom,passport;

int itemLeftLocally,itemLeftInForeign,discountAvail = 20,transportCostPerGroup = 400, group = 10;
int afterDiscountCostPerGroup = transportCostPerGroup
			- (discountAvail * transportCostPerGroup) / 100;
int no_of_gloves,no_of_masks;

//method definition
void convertVectorToVariables(vector<string> vs);
void normalBuy(int no_of_gloves,int no_of_masks,string passport,bool isPassport);
void optimizedBuyMethod(int no_of_gloves,int no_of_masks,string passport);
bool check(int no_of_gloves,int no_of_masks);
int optimizedBuy(int totalImport, int totalInventory, int totalForeignInventory, int itemPrice,int foriegnItemPrice,bool isDiscountApplicable);
int calculateTransportCost(bool isDiscountApplicable, int importItemCount);
    
int main() 
{   int a,b,c,d,ans=0;

    string s;
    cin>>s;
    vector<string>vs;
    string temp = "";
    
    for(char ch:s)
    {
        if(ch == ':' ) {vs.push_back(temp); temp = "";}
        else {temp += ch;}
    }
	
    //To add the last temp string
    vs.push_back(temp);

    convertVectorToVariables(vs);
    
    if(orderFrom=="UK" && passport=="UK"){
    {normalBuy(no_of_gloves,no_of_masks,passport,true);}
    } else if(orderFrom=="UK" && passport=="Germany"){
    {normalBuy(no_of_gloves,no_of_masks,passport,true);}
    } else if(orderFrom=="Germany" && passport=="Germany"){
    {optimizedBuyMethod(no_of_gloves,no_of_masks,passport);}
    }else if(orderFrom=="Germany" && passport=="UK")
    {optimizedBuyMethod(no_of_gloves,no_of_masks,passport);} 
    else if(orderFrom=="UK" && passport==""){
    normalBuy(no_of_gloves,no_of_masks,"",false);
    }
    else if(orderFrom=="Germany" && passport==""){
    ans+=optimizedBuy(no_of_gloves,50,100,150,100,false);
        a=itemLeftLocally;
        b=itemLeftInForeign;
    ans+=optimizedBuy(no_of_masks,100,100,100,65,false);
        c=itemLeftLocally;
        d=itemLeftInForeign;
    cout<<ans<<":"<<d<<":"<<c<<":"<<b<<":"<<a;
    }
	else
    {
     cout<<"WRONG INPUT STRING"<<endl;
     exit(0);   
    }
    return 0;
}

    void convertVectorToVariables(vector<string> vs)
    {
        if (vs.size() == 6) {
			//We can validate the passport string using regex. Assuming only valid passport are entered.
			orderFrom=vs[0];
            if(vs[1][0]=='B'){
            passport="UK";
            }
            else if(vs[1][0]=='A'){
                passport="Germany";
            }
			//To convert string to object
            stringstream obj,obj1;
            if(vs[2]=="Gloves"){
                obj << vs[3];
                obj >> no_of_gloves;
                obj1 << vs[5]; 
                obj1 >> no_of_masks;
            }else{
            obj << vs[3];
            obj >> no_of_masks;
            obj1 << vs[5]; 
            obj1 >> no_of_gloves;
            }
		}
		
		else if (vs.size() == 5) 
		{	//To convert string to object
			orderFrom=vs[0];
            stringstream obj,obj1;
            if(vs[1]=="Gloves"){
                obj << vs[2];
                obj >> no_of_gloves;
                obj1 << vs[4]; 
                obj1 >> no_of_masks;
            }else{
            obj << vs[2];
            obj >> no_of_masks;
            obj1 << vs[4]; 
            obj1 >> no_of_gloves;
            }
		} 
		else 
		{
			cout<<"WRONG INPUT STRING"<<endl;
            exit(0);
		}
    }
    
//Added this code to avoid for loop as we can normally calculate the total cost.   
void normalBuy(int no_of_gloves,int no_of_masks,string passport,bool isPassport)
{       
        if(check(no_of_gloves,no_of_gloves)){return;}
        
        int a,b,c,d,ans=0,cost;
        if(passport=="Germany"){cost=320;}
        else if(passport=="UK" || !isPassport){cost=400;}

    
        if(no_of_gloves<=100)
        {
            ans=ans+(no_of_gloves*100);
            c=100-no_of_gloves;
            d=50;
        }
        else
        {
            c=0;
            d=150-no_of_gloves;
            no_of_gloves-=100;
            
            ans+=100*100+(no_of_gloves*150);
            
            ans+=(no_of_gloves/10)*cost;
            
            if(no_of_gloves%10!=0){ans+=cost;}
        }
        
        if(no_of_masks<=100)
        {ans=ans+(no_of_masks*65);a=100-no_of_masks; b=100;}
        else
        {
            a=0;
            b=200-no_of_masks;
            no_of_masks-=100;
            ans+=(100*65)+(no_of_masks*100);
            ans+=(no_of_masks/10)*cost;
            if(no_of_masks%10!=0){ans+=cost;}
            
        }
        
        cout<<ans<<":"<<a<<":"<<b<<":"<<c<<":"<<d;
}

//Added this code specially for germany location where we need to optimize the buy method and to call the optimizedBuy
void optimizedBuyMethod(int no_of_gloves,int no_of_masks,string passport)
{
    if(check(no_of_gloves,no_of_gloves)){return;}
    int a,b,c,d;
    int ans=0;
    if(passport=="Germany"){
    ans+=optimizedBuy(no_of_gloves,50,100,150,100,false);
        a=itemLeftLocally;
        b=itemLeftInForeign;
    ans+=optimizedBuy(no_of_masks,100,100,100,65,false);
        c=itemLeftLocally;
        d=itemLeftInForeign;
    cout<<ans<<":"<<d<<":"<<c<<":"<<b<<":"<<a;
    }
    else{
    ans+=optimizedBuy(no_of_gloves,50,100,150,100,true);
        a=itemLeftLocally;
        b=itemLeftInForeign;
    ans+=optimizedBuy(no_of_masks,100,100,100,65,true); 
        c=itemLeftLocally;
        d=itemLeftInForeign;
     cout<<ans<<":"<<d<<":"<<c<<":"<<b<<":"<<a;
    }
    
}

//To check if we are out of stock
bool check(int no_of_gloves,int no_of_masks)
{
    if(no_of_gloves>150 || no_of_masks>200)
    {cout<<"OUT_OF_STOCK:100:100:100:50"; return true;}
    return false;
}

//Method to calculate the optimized no of items to buy locally or importing
int optimizedBuy(int totalImport, int totalInventory, int totalForeignInventory, int itemPrice,int foriegnItemPrice,bool isDiscountApplicable){
    int maxItemForImport = totalImport;
    int tempCost=0,cost=0;
    int transportCost;
    for (int itemForImport = 0; itemForImport <= maxItemForImport; itemForImport++) {
    int itemFromHomeLocation = totalImport - itemForImport;
    if (totalInventory < itemFromHomeLocation) {
    continue;
    }
    transportCost = calculateTransportCost(isDiscountApplicable, itemForImport);
    tempCost = itemFromHomeLocation * itemPrice + itemForImport * foriegnItemPrice + transportCost;
    if (cost == 0) {
    cost = tempCost;
    itemLeftLocally = totalInventory - itemFromHomeLocation;
    itemLeftInForeign = totalForeignInventory - itemForImport;
    } else {
    if (tempCost < cost) {
    cost = tempCost;
    itemLeftLocally = totalInventory - itemFromHomeLocation;
    itemLeftInForeign = totalForeignInventory - itemForImport;

}
}
           
}
    return cost;
}

int calculateTransportCost(bool isDiscountApplicable, int importItemCount) 
{
		int transportCost;
		if (importItemCount == 0) {
			transportCost = 0;
		} else {
			transportCost = isDiscountApplicable ? ((importItemCount - 1) / group + 1)
					* afterDiscountCostPerGroup : ((importItemCount - 1) / group + 1)
					* transportCostPerGroup;
		}
		return transportCost;
}
