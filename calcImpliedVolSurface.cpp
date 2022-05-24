//
// Calculate Implied Volatility 
//
// [in]:  double price                   : computes the volatility surface of an option chain
//        vector<double> strikes         : price of stock
//        vector<double> maturities:     : vector of maturities 
//        map<double, double> rates      : vector of risk-free interest rates
//        double dividend                : dividend yield of stock
// [out]: map of implied volatilities    : key is a pair<strike, maturity>
//
map<int,double> OptionCalc::calcImpliedVols(double price, 
                                            vector<double> opPrices,
                                            vector<int> strikes, 
                                            double rate, 
                                            double dividend, 
                                            double T, 
                                            char type)
{
    int j = 0;
    int cnt = 0;
    const double epsilon = 0.00001;
    map<int,double> opMap;
    vector<double>::iterator priceIter;
    double vol1 = 0.0;
    double error= = 0.0;
    double vol2 = 0.0;
    double vega = 0.0;
    double BSPrice = 0.0;
    double marketPrice = 0.0;
    int* strike = new int[strikes.size()];

    //copy strike prices stored in vectors
    //into array used in Newton-Raphson
    copy (strikes.begin(),
          strikes.end(),
          strike);

    //compute implied volatility for each option contract
    for (priceIter = opPrices.begin();
         priceIter != opPrices.end();
         priceIter++)
    {
        marketPrice = *priceIter;
        vol1 = 0.55;
        do
        {
            BSPrice = calcBSCallPrice(vol1,
                                      rate,
                                      dividend,
                                      strike[cnt],
                                      price,
                                      T);
            vega = calcVega(price,
                            strike[cnt],
                            rate,
                            dividend,
                            vol1,
                            T);
            vol2 = vol1 - (BSPrice - marketPrice)/(vega);
            error = vol2 - vol1;
            vol1 = vol2;
        } 
        while (abs(error) > epsilon);

        opMap[cnt] = vol1
        cnt++;
    }

    //print implied volatility
    for (j = 0; j < opMap.size(); j++)
        cout << opMap[j] << endl;
    
    // return a map of strikes and their implied volatility
    return opMap;
}