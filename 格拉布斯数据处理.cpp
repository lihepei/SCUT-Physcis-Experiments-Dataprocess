#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 计算平均值
double calculateMean(const vector<double>& data) {
    double sum = 0.0;
    for (double d : data) {
        sum += d;
    }
    return sum / data.size();
}

// 计算样本标准差
double calculateSampleStandardDeviation(const vector<double>& data, double mean) {
    double variance = 0.0;
    for (double d : data) {
        variance += pow(d - mean, 2);
    }
    variance /= data.size() - 1; // 使用 n-1 作为除数
    return sqrt(variance);
}

double per001_table[] = {-1,-1,-1,-1,1.155,1.492,1.749,1.944,2.097,2.231,2.323,2.410,2.485,2.550,2.607,2.659,2.705,2.747};//从3开始
double per005_table[] = {-1,-1,-1,-1,1.135,1.463,1.672,1.822,1.938,2.032,2.110,2.176,2.234,2.285,2.331,2.371,2.409,2.443};


// 计算格拉布斯准则的临界值
double calculateCriticalValue(int n, double significanceLevel) {
    if(significanceLevel == 0.05)
    	return per005_table[n];
    else
    	return per001_table[n];
}

int main() {
    int n;
    cout << "输入数据的数量(3<=n<=16): ";
    cin >> n;

    vector<double> data(n);
    cout << "输入数据点:\n";
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    double significanceLevel;
    cout << "输入显著水平 (0.05 或 0.01): ";
    cin >> significanceLevel;

    if (significanceLevel != 0.05 && significanceLevel != 0.01) {
        cout << "无效的显著水平输入。正在退出..." << endl;
        return 1;
    }

    double mean = calculateMean(data);
    double sampleStandardDeviation = calculateSampleStandardDeviation(data, mean);
    double stdDeviationOfMean = sampleStandardDeviation / sqrt(n);

    cout << "算术平均值: " << mean << endl;
    cout << "测量列的样本标准差σ: " << sampleStandardDeviation << endl;
    cout << "算术平均值标准偏差σx平均: " << stdDeviationOfMean << endl;

    // 格拉布斯法则剔除异常数据
    bool outliersDetected = true;
    int iteration = 1;
    while (outliersDetected) {
        outliersDetected = false;
        double criticalValue = calculateCriticalValue(data.size(), significanceLevel);
		mean = calculateMean(data);
		sampleStandardDeviation = calculateSampleStandardDeviation(data, mean);
        for (auto it = data.begin(); it != data.end(); ) {
            if (abs(*it - mean) > criticalValue * sampleStandardDeviation) {
                cout << "第 " << iteration << " 次检测到异常数据: " << *it << endl;
                it = data.erase(it);
                outliersDetected = true;
            } else {
                ++it;
            }
        }

        if (outliersDetected) 
            iteration++;
    }
    
    mean = calculateMean(data);
	sampleStandardDeviation = calculateSampleStandardDeviation(data, mean);
	stdDeviationOfMean = sampleStandardDeviation / sqrt(data.size());
	cout << "剔除异常数据后的算术平均值: " << mean << endl;
	cout << "剔除异常数据后的测量列的样本标准差σ: " << sampleStandardDeviation << endl;
	cout << "剔除异常数据后的算术平均值标准偏差σx平均: " << stdDeviationOfMean << endl;
	
	cout<<"为了计算均匀分布下测量值标准偏差，请输入Δ仪"<<endl;
	double yi;
	cin>>yi;
	double yi_stdDeviationOfMean = yi / (sqrt(3));
	cout<<"均匀分布下测量值标准偏差σ仪："<<yi_stdDeviationOfMean<<endl;
	double construct_StandardDeviation = sqrt(pow(stdDeviationOfMean,2)+pow(yi_stdDeviationOfMean,2));
	cout<<"合成标准差σ为"<<construct_StandardDeviation<<endl;
	cout<<"最终测量结果为 "<<mean<<" ±"<<construct_StandardDeviation<<" (请自行将误差向上保留一位小数，并将平均值对齐误差小数位)"<<endl;

    return 0;
}
