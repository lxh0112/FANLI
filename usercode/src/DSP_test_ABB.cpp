#include "UserAPI.h"
#include "UserDef.h"
//#include "MT_DSP_Lib.h"
#include <vector>
#include <iostream>
#include "cmath"
#include <algorithm>
#include <numeric> 
#include <sstream>
#include "CCS08F.h"
#include "RegDef.h"

//using namespace MuTest;
using namespace std;

int computeBinNumber (const int &Bin, const int &num_samples)
{      
    // this function computes distortion bin number based on tone bin, number of samples
    int band_bin= num_samples/2.0;

    double image    = Bin*1.0/band_bin;
    int   band     = image;
    int baseband_bin;
    if ( band % 2 == 0 )
            baseband_bin = Bin - band_bin * band;
    else
            baseband_bin = band_bin * (band+1) - Bin;

    return baseband_bin;
}
void adcDynamicCalc(const unsigned &FundBin, double *data, const unsigned &samplesCount, long Divided_Num,\
                    double &snr_i,\
                    double &snr_q,\
                    double &thd_i,\
                    double &thd_q,\
                    double &sfdr_i,\
                    double &sfdr_q,\
                    double &sinad_i,\
                    double &sinad_q,\
                    double &enob_i,\
                    double &enob_q,\
                    double &enob_iq,\
                    double &FullScalRange_i,\
                    double &FullScalRange_q,\
                    double &GainMismatch,\
                    const unsigned &distortion_num,\
                    const unsigned &SpurBin)
{
    long FFT_Size = samplesCount/2;
    if(FFT_Size > 0)
    {
        double tiny_number = 10e-20; //to avoid divide by 0, Log(0), etc.
        double Tone;
        double Fund_pwr_i=0;
        double Fund_pwr_q=0;
        double Harmonics=0;
        double Noise=0;
        double Spur=0;
        double *Pfft_i = new double[FFT_Size];
        double *Pfft_q = new double[FFT_Size];
        double data_i[FFT_Size];
        double data_q[FFT_Size];
        int hd_bin_i=0;
        int hd_bin_q=0;
        double *index_i;
        double *index_q;
    //    double Divided_Num = 1024;

        for(int i=0;i<FFT_Size;i++){
            data_i[i]=data[i*2];
            data_q[i]=data[i*2+1];
        }

    //    api->Set_curve_data("ADC_I", 0, 1/160e6, FFT_Size, data_i);   //打印FFT波形
    //    api->Set_curve_data("ADC_Q", 0, 1/160e6, FFT_Size, data_q);

//未解决        MT_FFT(api, FFT_Size, data_i, data_i, Pfft_i);
//未解决        MT_FFT(api, FFT_Size, data_q, data_q, Pfft_q);

        for(int i =0;i<FFT_Size/2;++i)
        {
            Pfft_i[i] = pow(Pfft_i[i],2)*2;
            Pfft_q[i] = pow(Pfft_q[i],2)*2;
        }
        int tone_bin = computeBinNumber (FundBin, FFT_Size);
        int spur_bin = computeBinNumber (SpurBin, FFT_Size);

        /*calc I*/
        Pfft_i[0]= 0; //ignore dc value here
        Pfft_i[1]= 0; //ignore dc value here
        Pfft_i[2]= 0; //ignore dc value here

        Tone = Pfft_i[tone_bin];
        Tone += tiny_number;
        FullScalRange_i = sqrt(Tone);

        for(int m=-2;m<=2;m++){
            Fund_pwr_i = Fund_pwr_i +  Pfft_i[tone_bin+m];
            Pfft_i[tone_bin+m] = 0;
        }

        Fund_pwr_i += tiny_number;

        Pfft_i[spur_bin]= 0;   //ignore 40M spur value here
        index_i = max_element(Pfft_i, Pfft_i+FFT_Size/4);
        Spur = *(index_i);
        Spur += tiny_number;

        for(unsigned i=2; i<distortion_num+1; ++i) {
            hd_bin_i = computeBinNumber (i*FundBin, FFT_Size);
            Harmonics += Pfft_i[hd_bin_i];
            Pfft_i[hd_bin_i] = 0;
        }
        Harmonics += tiny_number;

        Noise = std::accumulate(Pfft_i, Pfft_i+FFT_Size/4, 0.0) + tiny_number;

        snr_i   = log10(Fund_pwr_i/Noise) * 10;
        thd_i   = log10(Fund_pwr_i/Harmonics) * 10;
        sinad_i = log10(Fund_pwr_i/(Noise+Harmonics)) * 10;
        sfdr_i  = log10(Fund_pwr_i/Spur) * 10;
        enob_i  =(sinad_i-1.76 + 20*log10(Divided_Num/(FullScalRange_i*2)))/6.02;

        Harmonics=0;
        Noise=0;
        Spur=0;

        /*calc Q*/
        Pfft_q[0]= 0; //ignore dc value here
        Pfft_q[1]= 0; //ignore dc value here
        Pfft_q[2]= 0; //ignore dc value here

        Tone = Pfft_q[tone_bin];
        Tone += tiny_number;
        FullScalRange_q = sqrt(Tone);

        for(int m=-2;m<=2;m++){
            Fund_pwr_q = Fund_pwr_q +  Pfft_q[tone_bin+m];
            Pfft_q[tone_bin+m] = 0;
        }

        Fund_pwr_q += tiny_number;

        Pfft_q[spur_bin]= 0;   //ignore 40M spur value here
        index_q = max_element(Pfft_q, Pfft_q+FFT_Size/4);
        Spur = *(index_q);
        Spur += tiny_number;

        for(unsigned i=2; i<distortion_num+1; ++i) {
            hd_bin_q = computeBinNumber (i*FundBin, FFT_Size);
            Harmonics += Pfft_q[hd_bin_q];
            Pfft_q[hd_bin_q] = 0;
        }
        Harmonics += tiny_number;

        Noise = std::accumulate(Pfft_q, Pfft_q+FFT_Size/4, 0.0) + tiny_number;

        snr_q   = log10(Fund_pwr_q/Noise) * 10;
        thd_q   = log10(Fund_pwr_q/Harmonics) * 10;
        sinad_q = log10(Fund_pwr_q/(Noise+Harmonics)) * 10;
        sfdr_q  = log10(Fund_pwr_q/Spur) * 10;
        enob_q  =(sinad_q - 1.76 + 20*log10(Divided_Num/(FullScalRange_q*2)))/6.02;

        if(FullScalRange_q){
            GainMismatch = 20 * log10(FullScalRange_i/FullScalRange_q);
        }

        enob_iq = (-10 * log10(pow(10 , (-(enob_i * 6.02 + 1.76)/10.0)) + pow(10 , (-(enob_q * 6.02 + 1.76)/10.0))) + 3 - 1.76) / 6.02;

        delete[] Pfft_i;
        delete[] Pfft_q;
    }
    else
    {
        snr_i   = 999.0;
        thd_i   = 999.0;
        sinad_i = 999.0;
        sfdr_i  = 999.0;
        enob_i  = 999.0;
        FullScalRange_i = 999.0;
        
        snr_q   = 999.0;
        thd_q   = 999.0;
        sinad_q = 999.0;
        sfdr_q  = 999.0;
        enob_q  = 999.0;
        FullScalRange_q = 999.0;
        
        GainMismatch = 999.0;
        enob_iq = 999.0;
    }
    return;

}

void dacDynamicCalc(const unsigned &FundBin, IQMeasureAttribute *IQMeasData, const unsigned &samplesCount,\
                    double &FullScalRange_i,\
                    double &FullScalRange_q,\
                    double &dc_offset_i,\
                    double &dc_offset_q,\
                    double &snr_i,\
                    double &snr_q,\
                    double &thd_i,\
                    double &thd_q,\
                    double &sfdr_i,\
                    double &sfdr_q,\
                    double &sinad_i,\
                    double &sinad_q,\
                    double &enob_i,\
                    double &enob_q,\
                    double &GainMismatch,\
                    const unsigned &distortion_num)
{
   
    unsigned FFT_Size = samplesCount/2;
    if(FFT_Size > 0){
        double tiny_number = 10e-20; //to avoid divide by 0, Log(0), etc.
        double Tone;
        double Fund_pwr_i = 0;
        double Fund_pwr_q = 0;
        double Harmonics=0;
        double Noise=0;
        double Spur=0;
        double *Inreal = new double[FFT_Size];
        double *Inimag = new double[FFT_Size];
        double *SpectrumTemp_I = new double[FFT_Size];
        double *SpectrumTemp_Q = new double[FFT_Size];

        long inputAmp = -11;
        double Vpk_offset = 1.1;

        for(int i = 0; i < FFT_Size; i++)
        {
            Inreal[i] = IQMeasData->pComplexData[i].real;
            Inimag[i] = IQMeasData->pComplexData[i].imaginary;
        }

    //    api->Set_curve_data("DAC_I", 0, 1/160e6, FFT_Size, Inreal);   //打印FFT波形
    //    api->Set_curve_data("DAC_Q", 0, 1/160e6, FFT_Size, Inimag);

//未解决        MT_FFT(api, FFT_Size, Inreal, Inreal, SpectrumTemp_I);
//未解决        MT_FFT(api, FFT_Size, Inimag, Inimag, SpectrumTemp_Q);

        for(unsigned i =0;i<FFT_Size;++i)
        {
            SpectrumTemp_I[i] = pow(SpectrumTemp_I[i]*2,2)*2;
            SpectrumTemp_Q[i] = pow(SpectrumTemp_Q[i]*2,2)*2;
        }
        int tone_bin = computeBinNumber (FundBin, samplesCount);

        /*calc I*/
        dc_offset_i= sqrt(SpectrumTemp_I[0]);
        SpectrumTemp_I[0]= 0;
        SpectrumTemp_I[1]= 0;
        SpectrumTemp_I[2]= 0;

        Tone = SpectrumTemp_I[tone_bin];    
        Tone += tiny_number;
        FullScalRange_i = sqrt(Tone) * Vpk_offset;    //add for loss 

        for(int m=-2;m<=2;m++){
            Fund_pwr_i = Fund_pwr_i +  SpectrumTemp_I[tone_bin+m];
            SpectrumTemp_I[tone_bin+m] = 0;
        }

        Fund_pwr_i += tiny_number;
        
        for(unsigned i=2; i<distortion_num+1; ++i) {
            int hd_bin = computeBinNumber (i*FundBin, samplesCount);
            Harmonics += SpectrumTemp_I[hd_bin];
            SpectrumTemp_I[hd_bin] = 0;
        }
        Harmonics += tiny_number;
        
        double *index_i;
        index_i = max_element(SpectrumTemp_I, SpectrumTemp_I+FFT_Size/4);
        Spur = *(index_i);
        Spur += tiny_number;

        Noise = std::accumulate(SpectrumTemp_I, SpectrumTemp_I+FFT_Size/4, 0.0) + tiny_number;
        snr_i   = log10(Fund_pwr_i/Noise) * 10;
        thd_i   = log10(Fund_pwr_i/Harmonics) * 10;
        sinad_i = log10(Fund_pwr_i/(Noise+Harmonics)) * 10;
        sfdr_i  = log10(Fund_pwr_i/Spur) * 10;
        enob_i=(sinad_i - 1.76 - inputAmp)/6.02;

        Harmonics=0;
        Noise=0;
        Spur=0;

        /*calc Q*/
        dc_offset_q= sqrt(SpectrumTemp_Q[0]);
        SpectrumTemp_Q[0]= 0;

        Tone = SpectrumTemp_Q[tone_bin];
        Tone += tiny_number;
        FullScalRange_q = sqrt(Tone) * Vpk_offset;   //add for loss 

        for(int m=-2;m<=2;m++){
            Fund_pwr_q = Fund_pwr_q +  SpectrumTemp_Q[tone_bin+m];
            SpectrumTemp_Q[tone_bin+m] = 0;
        }

        Fund_pwr_q += tiny_number;

        for(unsigned i=2; i<distortion_num+1; ++i) {
            int hd_bin = computeBinNumber (i*FundBin, samplesCount);
            Harmonics += SpectrumTemp_Q[hd_bin];
            SpectrumTemp_Q[hd_bin] = 0;
        }
        Harmonics += tiny_number;
        
        double *index_q;
        index_q = max_element(SpectrumTemp_Q, SpectrumTemp_Q+FFT_Size/4);
        Spur = *(index_q);
        Spur += tiny_number;

        Noise = std::accumulate(SpectrumTemp_Q, SpectrumTemp_Q+FFT_Size/4, 0.0) + tiny_number;
        snr_q   = log10(Fund_pwr_q/Noise) * 10;
        thd_q   = log10(Fund_pwr_q/Harmonics) * 10;
        sinad_q = log10(Fund_pwr_q/(Noise+Harmonics)) * 10;
        sfdr_q  = log10(Fund_pwr_q/Spur) * 10;
        enob_q=(sinad_q - 1.76 - inputAmp)/6.02;

        if(FullScalRange_q){
            GainMismatch = 20 * log10(FullScalRange_i/FullScalRange_q);
        }

        delete[] SpectrumTemp_I;
        delete[] SpectrumTemp_Q;
        delete[] Inreal;
        delete[] Inimag;
    }
    else
    {
        snr_i   = 999.0;
        thd_i   = 999.0;
        sinad_i = 999.0;
        sfdr_i  = 999.0;
        enob_i  = 999.0;
        FullScalRange_i = 999.0;
        
        snr_q   = 999.0;
        thd_q   = 999.0;
        sinad_q = 999.0;
        sfdr_q  = 999.0;
        enob_q  = 999.0;
        FullScalRange_q = 999.0;
        
        GainMismatch = 999.0;
    }
    return;
}

vector<double> BestFitAnalysis (double *Samples,const int &samplesCount, double INLResults[], double DNLResults[])
{
    vector<double> result(12);
    //Regression line to minimize the square sum error: Y=a+bX, find a and b. b=LSB
    // SP=Sum(XY)-Sum(X)Sum(Y)/n, SSx=Sum(X^2)-(Sum(X)^2)/n
    // b=SP/SSx, a=AVG(Y)-bAVG(X)

    double sum_xy=0,sum_x=0,sum_y=0,sum_x_square=0;
    double y;
    for (int x=0; x<samplesCount; x++) {
        y = Samples[x];
        sum_xy = sum_xy + x*y;
        sum_x = sum_x + x;
        sum_y = sum_y + y;
        sum_x_square = sum_x_square + pow((double)x,2);
    }
    double SP = sum_xy-(sum_x * sum_y )/samplesCount ;
    double SSx = sum_x_square - pow((double)sum_x, 2)/samplesCount;

    double b=SP/SSx; //lsb
    double a=(sum_y - b*sum_x)/samplesCount;

    double entry1, entry2;
    DNLResults[0]=0.0;
    INLResults[0] = (Samples[0]-a)/b;

    for(int x=1; x<samplesCount; x++){
        entry1=Samples[x-1];
        entry2=Samples[x];
        DNLResults[x] = (entry2-entry1-b)/b;
        INLResults[x] = (entry2-(a+b*x))/b;
    }
    double *ptr = DNLResults;
    double *index;
    index = max_element(ptr, ptr+samplesCount);
    result[1] = index - ptr;
    result[0] = *(index);
    index = min_element(ptr, ptr+samplesCount);
    result[3] = index - ptr;
    result[2] = *(index);
    ptr = INLResults;
    index = max_element(ptr, ptr+samplesCount);
    result[5]  = index - ptr;
    result[4] = *(index);
    index = min_element(ptr, ptr+samplesCount);
    result[7] = index - ptr;
    result[6] = *(index);
    
    result[8] = b;
    result[9] = Samples[0];
    result[10] = Samples[samplesCount-1];
    result[11] = a;

//    return move(result);
}
vector<double> EndPointAnalysis (double *Samples,const int &samplesCount, double *INLResults, double *DNLResults)
{
    vector<double> result(11);
    double top_val=Samples[samplesCount-1], bot_val=Samples[0];
    double lsb=(top_val-bot_val)/(samplesCount-1);

    double entry1, entry2;
    DNLResults[0]=0.0;
    INLResults[0]=0.0;
    
    for(int i=1; i<samplesCount; i++){
        entry1 = Samples[i-1];
        entry2 = Samples[i];
        DNLResults[i]=(entry2-entry1-lsb)/lsb;
        INLResults[i]=INLResults[i-1]+DNLResults[i];
    }
    double *ptr = DNLResults;
    double *index;
    index = max_element(ptr, ptr+samplesCount);
    result[1] = index - ptr;
    result[0] = *(index);
    index = min_element(ptr, ptr+samplesCount);
    result[3] = index - ptr;
    result[2] = *(index);
    ptr = INLResults;
    index = max_element(ptr, ptr+samplesCount);
    result[5]  = index - ptr;
    result[4] = *(index);
    index = min_element(ptr, ptr+samplesCount);
    result[7] = index - ptr;
    result[6] = *(index);
    
    result[8] = lsb;
    result[9] = bot_val;
    result[10] = top_val;
//    return move(result);
}

 enum STATIC_ANALYSIS_TYPE {
     BEST_FIT_ANALYSIS,    
     END_POINT_ANALYSIS               
 };
 
void dacStaticCalc(double *Data, const unsigned &samplesCount,double &offset, double &fsr, double &inl, double &dnl, unsigned &monotonic, STATIC_ANALYSIS_TYPE AnalysisType)
{
    double *INLResults,*DNLResults;
    INLResults = new double[samplesCount];
    DNLResults = new double[samplesCount];
    
    vector<double> Results;
    monotonic = 0;
    for(unsigned i = 0; i < samplesCount-1; ++i)
    {
        if( Data[i] > Data[i+1] ) ++monotonic;
    }
    if (AnalysisType == BEST_FIT_ANALYSIS)
    {
        Results = BestFitAnalysis(Data, samplesCount, INLResults, DNLResults);
    }
    else if (AnalysisType == END_POINT_ANALYSIS)
    {
        Results = EndPointAnalysis(Data, samplesCount, INLResults, DNLResults);
    }
   
    offset = Results[9];   
    fsr = Results[10];      

    //dnl in LSBs
    if ( abs(Results[0]) > abs(Results[2]) )
        dnl = Results[0];
    else
        dnl = Results[2];
    // inl in LSBs
    if ( abs(Results[4]) > abs(Results[6]) )
        inl= Results[4];
    else
        inl = Results[6];

    std::stringstream info;
    info << "offset is "<< offset << std::endl;
    info << "fsr is   "<< fsr << std::endl;
    info << "inl is    "<< inl << std::endl;
    info << "dnl is    "<< dnl << std::endl;
    info << "dnl Max is "<< Results[0]<<"  -->> Index is "<< Results[1] << std::endl;
    info << "dnl Min is "<< Results[2]<<"  -->> Index is "<< Results[3] << std::endl;
    info << "inl Max is "<< Results[4]<<"  -->> Index is "<< Results[5] << std::endl;
    info << "inl Min is "<< Results[6]<<"  -->> Index is "<< Results[7] << std::endl;

//不确定    api->Info_message(info.str().c_str());
    cout<<"info.str().c_str()"<<endl;

    delete [] INLResults;
    delete [] DNLResults;
}

vector<double> HistogramAnalysis(int* Samples, const int &samplesCount, const int &nADCCodes, const double &Vmin, const double &Vmax,double *INLResults, double *DNLResults)
{
    int     code_index = 0;
    double average_hit = 0;
    double* code_histogram = NULL;
    int missing_code = 0;
    vector<double> result(12);
    code_histogram = new double[nADCCodes];
    
    for (int i = 0; i < nADCCodes; i++ )
        code_histogram[i] = 0.0 ;

    for (int i = 0; i < samplesCount; i++ )
    {
        if (Samples[i] < 0)
        {
            delete [] code_histogram;
//            return vector<double>{99,0,-99,0,99,0,-99,0,99,0,0}; //error result
        }

        code_index = Samples[i] + 1;
        if (code_index > nADCCodes)
        {

            delete [] code_histogram;
//            return vector<double>{99,0,-99,0,99,0,-99,0,99,0,0}; //error result;
        }

        code_histogram[code_index-1] = 1.0 + code_histogram[code_index-1];
    }

    if (code_histogram[0] == 0) ++missing_code;
    for (int i = 1; i < nADCCodes-1; i++ )
    {
       average_hit+=code_histogram[i];
       if (code_histogram[i] == 0) ++missing_code;
    }
    average_hit = average_hit/ (nADCCodes - 2);
    
    DNLResults[0]=0.0;
    INLResults[0]=0.0;
    DNLResults[nADCCodes - 1]=0.0;
    INLResults[nADCCodes - 1]=0.0;
    
    for (int i = 1; i < nADCCodes-1; i++ )
    {
        DNLResults[i] = (code_histogram[i] - average_hit)/average_hit;
        INLResults[i]=INLResults[i-1]+DNLResults[i-1];
    }
    
    double *ptr = DNLResults;
    double *index;
    index = max_element(ptr, ptr+nADCCodes);
    result[1] = index - ptr;
    result[0] = *(index);
    index = min_element(ptr, ptr+nADCCodes);
    result[3] = index - ptr;
    result[2] = *(index);
    ptr = INLResults;
    index = max_element(ptr, ptr+nADCCodes);
    result[5]  = index - ptr;
    result[4] = *(index);
    index = min_element(ptr, ptr+nADCCodes);
    result[7] = index - ptr;
    result[6] = *(index);

    double lsbv = (Vmax - Vmin)/(samplesCount-1);
    if(code_histogram[0] < 1) 
        result[9] = 1000;
    else
        result[9]  = Vmin + code_histogram[0]*lsbv;
    if (code_histogram[nADCCodes - 1] < 1)
        result[10] = -1000;
    else
        result[10] = Vmax - code_histogram[nADCCodes - 1]*lsbv;
    
    result[8]  = lsbv *average_hit;
    result[11] = missing_code;
    delete [] code_histogram;
//    return move(result);
}

void adcStaticCalc(int *Data, const unsigned &samplesCount, const double &Vo_in, const double &Vn_in, const int &AdcBits,
                   double &offset, double &gain, double &inl, double &dnl, unsigned &missingCode)
{
    double *INLResults,*DNLResults;
    int nADCCodes = pow(2,AdcBits);

    INLResults = new double[nADCCodes];
    DNLResults = new double[nADCCodes];
    vector<double> Results;
    
    Results = HistogramAnalysis(Data, samplesCount, nADCCodes, Vo_in, Vn_in, INLResults, DNLResults);
    offset = Results[9];    //Vo
    gain = Results[10];     //Vn
    missingCode = Results[11];
    //dnl in LSBs
    if ( abs(Results[0]) > abs(Results[2]) )
        dnl = Results[0];
    else
        dnl = Results[2];
    // inl in LSBs
    if ( abs(Results[4]) > abs(Results[6]) )
        inl= Results[4];
    else
        inl = Results[6];


            
    std::stringstream info;
    info << "offset is "<< offset << std::endl;
    info << "gain is   "<< gain << std::endl;
    info << "inl is    "<< inl << std::endl;
    info << "dnl is    "<< dnl << std::endl;
    info << "dnl Max is "<< Results[0]<<"  -->> Index is "<< Results[1] << std::endl;
    info << "dnl Min is "<< Results[2]<<"  -->> Index is "<< Results[3] << std::endl;
    info << "inl Max is "<< Results[4]<<"  -->> Index is "<< Results[5] << std::endl;
    info << "inl Min is "<< Results[6]<<"  -->> Index is "<< Results[7] << std::endl;

//不确定    api->Info_message(info.str().c_str());
     cout<<"info.str().c_str()"<<endl;
            
    delete [] INLResults;
    delete [] DNLResults;
}
