#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// ����ƽ��ֵ
double calculateMean(const vector<double>& data) {
    double sum = 0.0;
    for (double d : data) {
        sum += d;
    }
    return sum / data.size();
}

// ����������׼��
double calculateSampleStandardDeviation(const vector<double>& data, double mean) {
    double variance = 0.0;
    for (double d : data) {
        variance += pow(d - mean, 2);
    }
    variance /= data.size() - 1; // ʹ�� n-1 ��Ϊ����
    return sqrt(variance);
}

double per001_table[] = {-1,-1,-1,-1,1.155,1.492,1.749,1.944,2.097,2.231,2.323,2.410,2.485,2.550,2.607,2.659,2.705,2.747};//��3��ʼ
double per005_table[] = {-1,-1,-1,-1,1.135,1.463,1.672,1.822,1.938,2.032,2.110,2.176,2.234,2.285,2.331,2.371,2.409,2.443};


// ���������˹׼����ٽ�ֵ
double calculateCriticalValue(int n, double significanceLevel) {
    if(significanceLevel == 0.05)
    	return per005_table[n];
    else
    	return per001_table[n];
}

int main() {
    int n;
    cout << "�������ݵ�����(3<=n<=16): ";
    cin >> n;

    vector<double> data(n);
    cout << "�������ݵ�:\n";
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    double significanceLevel;
    cout << "��������ˮƽ (0.05 �� 0.01): ";
    cin >> significanceLevel;

    if (significanceLevel != 0.05 && significanceLevel != 0.01) {
        cout << "��Ч������ˮƽ���롣�����˳�..." << endl;
        return 1;
    }

    double mean = calculateMean(data);
    double sampleStandardDeviation = calculateSampleStandardDeviation(data, mean);
    double stdDeviationOfMean = sampleStandardDeviation / sqrt(n);

    cout << "����ƽ��ֵ: " << mean << endl;
    cout << "�����е�������׼���: " << sampleStandardDeviation << endl;
    cout << "����ƽ��ֵ��׼ƫ���xƽ��: " << stdDeviationOfMean << endl;

    // ������˹�����޳��쳣����
    bool outliersDetected = true;
    int iteration = 1;
    while (outliersDetected) {
        outliersDetected = false;
        double criticalValue = calculateCriticalValue(data.size(), significanceLevel);
		mean = calculateMean(data);
		sampleStandardDeviation = calculateSampleStandardDeviation(data, mean);
        for (auto it = data.begin(); it != data.end(); ) {
            if (abs(*it - mean) > criticalValue * sampleStandardDeviation) {
                cout << "�� " << iteration << " �μ�⵽�쳣����: " << *it << endl;
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
	cout << "�޳��쳣���ݺ������ƽ��ֵ: " << mean << endl;
	cout << "�޳��쳣���ݺ�Ĳ����е�������׼���: " << sampleStandardDeviation << endl;
	cout << "�޳��쳣���ݺ������ƽ��ֵ��׼ƫ���xƽ��: " << stdDeviationOfMean << endl;
	
	cout<<"Ϊ�˼�����ȷֲ��²���ֵ��׼ƫ������릤��"<<endl;
	double yi;
	cin>>yi;
	double yi_stdDeviationOfMean = yi / (sqrt(3));
	cout<<"���ȷֲ��²���ֵ��׼ƫ����ǣ�"<<yi_stdDeviationOfMean<<endl;
	double construct_StandardDeviation = sqrt(pow(stdDeviationOfMean,2)+pow(yi_stdDeviationOfMean,2));
	cout<<"�ϳɱ�׼���Ϊ"<<construct_StandardDeviation<<endl;
	cout<<"���ղ������Ϊ "<<mean<<" ��"<<construct_StandardDeviation<<" (�����н�������ϱ���һλС��������ƽ��ֵ�������С��λ)"<<endl;

    return 0;
}
