//Here the requirement is to find a order combination which can be executed with QO excess volume.
//In this algorithm we would go through all the combinations and select the applicable orders using a pattern.
//Here all the orders are numbered as per the position at the list and if combination number divided
//by that number is an odd number, that particular order is applicable for that combination.
                 
bool BruteForceAlgo::runAlgo(double execessVolume, list<Order*> *aggressiveSide, list<Order*> *contraSide)
{
        int noOfOrders = contraSide->size() + aggressiveSide->size();
        int noOfCombinations = pow(2, noOfOrders );
        double totoalQty = 0.0;
        double totalMaq = 0.0;
        int temp = 0;
        int position = 0;
 
        for (int i = 0; i <= noOfCombinations; i++) {
 
                totalQty = 0.0;
                totalMaq = 0.0;
 
                position = 0;
                for (auto order : *contraSide) {
 
                        temp = (i / pow(2, position));
                        if (temp % 2 == 1)
                        {
                                totalMaq += order->m_maq;
                                totalQty += order->m_orderQty;
                        }
                        position++;
 
                }
                //If there are any orders in the same side, those will be considered for the combinations as well.
                for (auto order : *aggressiveSide) {
 
                        temp = (i / pow(2, position));
                        if (temp % 2 == 1)
                        {
                                totalMaq -= order->m_orderQty;
                                totalQty -= order->m_maq;
                        }
                        position++;
 
                }
                //If excess volume falls between total maq and totaol qty, this is a possible combination.
                if (totalMaq <= execessVolume && execessVolume <= totalQty)
                {
                        // This is a possible combination to fill excess volume
                        //cout << "\t=> { " << totalMaq << ", " << totalQty << "}" << endl;
                         
                        return true;
                }
        }
 
        return false;
}