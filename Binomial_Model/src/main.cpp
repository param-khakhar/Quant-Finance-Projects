#include<bits/stdc++.h>
using namespace std;

double Payoff(double S, double K){
    double ans = 0;
    if(S > K)
        ans = S - K;
    return ans;
}

double Price(double asset, double volatility, double rate, double strike, double expiry, int steps){
    vector<double> S(steps+1);
    vector<double> V(steps+1);

    double timestep = expiry/steps;
    double discountFactor = exp(rate * timestep * -1);

    double temp1 = exp((rate + volatility * volatility)*timestep);
    double temp2 = 0.5 * (discountFactor + temp1);
    double u = temp2 + sqrt(temp2 * temp2 - 1);
    double d = 1/u;
    double p = (exp(rate * timestep) - d) / (u-d);

    S[0] = asset;

    // In each iteration we are essentially initializing each row of the tree

    for(int n=1;n<=steps;n++){
        for(int j=n;j>=1;j--){
            S[j] = u * S[j-1];
        }
        S[0] = d * S[0];
    }

    // Last row of the tree

    for(int j=0;j<=steps;j++){
        V[j] = Payoff(S[j], strike);
    }
    
    for(int n=steps;n>=1;n--){
        for(int j=0;j<=n-1;j++){
            V[j] = (p * V[j+1] + (1-p) * V[j]) * discountFactor;
        }
    }
    double price = V[0];
    return price;
}


int main(){
    double asset, volatility, rate, strike, expiry;
    int steps;
    cout<<"Option Price Calculator using Binomial Model\n";
    cout<<"============================================\n";
    cout<<"\n";
    cout<<"Enter Asset Price:";
    cin>>asset;
    cout<<"Enter Volatility:";
    cin>>volatility;
    cout<<"Enter Risk Free Rate:";
    cin>>rate;
    cout<<"Enter Strike:";
    cin>>strike;
    cout<<"Enter Expiry in Years:";
    cin>>expiry;
    cout<<"Enter Number of Steps (Months):";
    cin>>steps;

    cout<<"\n\n";
    cout<<"The current value of the option is: "<<Price(asset, volatility, rate, strike, expiry, steps)<<"\n";
    return 0;
}