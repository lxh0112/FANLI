/* 
 * File:   CCFFT.h
 * Author: Administrator
 *
 * Created on 2021年3月30日, 下午5:40
 */

#ifndef CC_FFT_H
#define	CC_FFT_H

#ifndef DLLAPI
#define DLLAPI  __declspec(dllexport)
#endif

namespace CCDSP
{
     typedef enum{
        _0_Ohm = 0,
        _1_Ohm = 1,
        _50_Ohm = 50
    }LoadImpedance;

    typedef struct{
        double real;
        double imag;
    }Complex_t,*P_Complex_t;

    typedef struct{
        float InitiaFrequency;
        float FrequencyResolution;
        float* pSpectrumData;
        long dwNumbersOfSpectrum;
        float PeakAmplitude;
        float PeakFrequency;
    }SPECTRUM_TYPE,*P_SPECTRUM_TYPE;

    typedef enum{
        RECT = 0,
        HANNING,
        HAMMING,
        FLATTOP,
        GAUSS,
        TYPE_END
    }FFT_WIND_TYPE;

    typedef struct{
        double snr;
        double sinad;
        double thd;
        double sfdr;
        double ENOB;
    }DynamicParam_t;

    #define CCDSP_DEFINE_COMPLEX(R, C) typedef R C[2]

    #define CCDSP_CONCAT(prefix, name) prefix ## name
    #define CCDSP_MANGLE_DOUBLE(name) CCDSP_CONCAT(CCDSP_, name)
    #define CCDSP_MANGLE_FLOAT(name) CCDSP_CONCAT(CCDSP_, name)
    #define CCDSP_MANGLE_NAME(name) name
    /*
    huge second-order macro that defines prototypes for all API
    functions.  We expand this macro for each supported precision
    
    X: name-mangling macro
    R: real data type
    */
    #define CCDSP_DEFINE_API(X, R)					                    \
    DLLAPI bool X(FFT)(R IData[],R QData[],long nSize,R* pOutData,LoadImpedance loadImpedance = _50_Ohm,bool bShift = true);		            \
    DLLAPI bool X(FFT)(R realData[],long nSize,R* pOutData,LoadImpedance loadImpedance = _50_Ohm,FFT_WIND_TYPE windType = RECT);    \
    DLLAPI R X(SNR)(R FFT[],long lSize,R Fs,R Fund,R Fmin = -1,R Fmax = -1,int nHarm = 5);      \
    DLLAPI R X(THD)(R FFT[], long lSize, R Fs, R Fund, int nHarm = 5);      \
    DLLAPI R X(SINAD)(R FFT[], long lSize, R Fs, R Fund, R Fmin = -1,R Fmax = -1,int nHarm = 5);   \
    DLLAPI R X(SFDR)(R FFT[], long lSize, R Fs, R Fmin = -1,R Fmax = -1);   \
    DLLAPI DynamicParam_t X(CalcParam)(R FFT[],long lSize,long lSidelobe = 0,int nHarm = 5);      \
    DLLAPI bool X(SPECTRUM)(R IData[],R QData[],long nSize,R Fs,P_SPECTRUM_TYPE pOutData,LoadImpedance loadImpedance = _50_Ohm);\

    /*
    * @param complex_in: Array of size N on which to perform FFT calculation.
    * @param nSize: the size of the array data, the I and Q size must be same.
    * @param pFFTOut:the FFT out array data.
    */
    DLLAPI bool FFT(Complex_t complex_in[],long nSize,P_Complex_t pFFTOut);
    /*
    * @param realData: Array of size N on which to perform FFT calculation.
    * @param nSize: the size of the array data.
    * @param pFFTOut:the FFT out array data.
    */
    DLLAPI bool FFT(double realData[],long nSize,P_Complex_t pFFTOut);

    /*
    * @param IData: Array of size N on which to perform FFT calculation.
    * @param QData: Array of size N on which to perform FFT calculation.
    * @param nSize: the size of the array data, the I and Q size must be same.
    * @param pOutData:the out array data. if loadImpedance is 0,the data is Vrms,other is magnitude.
    * @param loadImpedance: the impedance use for calculate the dbm. only supply 0 ohm(Vrms), 1 ohm and 50 ohm.
    * @param bShift:specifies whether the DC component is at the center of FFT. The default is True. 
    * DLLAPI bool FFT(double IData[],double QData[],long nSize,double* pOutData,LoadImpedance loadImpedance = _50_Ohm,bool bShift = true);
    * DLLAPI bool FFT(float IData[],float QData[],long nSize,float* pOutData,LoadImpedance loadImpedance = _50_Ohm,bool bShift = true);
    */

    
    /*
    * @param IData : Array of size N on which to perform FFT calculation.
    * @param QData : Array of size N on which to perform FFT calculation.
    * @param nSize : the size of the array data, the I and Q size must be same.
    * @param Fs: Sampling Frequency (Fs) used when digitizing waveform.
    * @param pOutData:the struct of spectrum data. if loadImpedance is 0,the data is Vrms,other is magnitude.
    * @param loadImpedance: the impedance use for calculate the dbm. only supply 0 ohm(Vrms), 1 ohm and 50 ohm.
    * DLLAPI bool SPECTRUM(double IData[],double QData[],long nSize,double Fs,P_SPECTRUM_TYPE pOutData,LoadImpedance loadImpedance = _50_Ohm);
    * DLLAPI bool SPECTRUM(float IData[],float QData[],long nSize,float Fs,P_SPECTRUM_TYPE pOutData,LoadImpedance loadImpedance = _50_Ohm);
    *
    */

    /**
     * Computes SNR (Signal to Noise) out of a FFT.
     *          SNR : Ratio of the rms value of the fundamental signal
     *                to the mean value of the root-sum-square (rss) of all
     *                other spectral components, excluding all harmonics.
     * @param FFT		FFT Array on which to compute SNR.
     * @param lSize	Size of FFT_Array.
     * @param Fs	Sampling Frequency (Fs) used when digitizing waveform.
     * @param Fund	Frequency of Fundamental.
     * @param Fmin 	Start Frequency of Range to consider in SFDR calculation.
     * @param Fmax 	Stop Frequency of Range to consider in SFDR calculation.
     * @note		Function returns SNR in dB relative to Fundamental.
     * DLLAPI float SNR(float FFT[],long lSize,float Fs,float Fund,float Fmin,float Fmax);
     */

    /**
     * Computes THD (Total Harmonic Distorsion) out of a FFT.<br>
     *          THD : Ratio of the rms value of the fundamental signal
     *                to the mean value of the root-sum-square of its harmonics.
     * @param FFT		FFT Array on which to compute THD.
     * @param lSize	    Size of FFT_Array.
     * @param Fs		Sampling Frequency (Fs) used when digitizing waveform.
     * @param F_Fund	Frequency of Fundamental.
     * @param NHarm		Number of Harmonics to condider in THD Calculation.
     * @note		    Function returns THD in dB relative to Fundamental.
     * DLLAPI float THD(float FFT[], long lSize, float Fs, float Fund, int NHarm);
     */


    /**
     * Computes SINAD (Signal to Noise and Distortion Ratio) out of a FFT.<br>
     *          SINAD : Ratio of the rms value of the fundamental signal
     *                  to the mean value of the root-sum-square (rss) of all
     *                  other spectral components, including harmonics.
     * @param FFT		FFT Array on which to compute SINAD.
     * @param lSize	    Size of FFT_Array.
     * @param Fs		Sampling Frequency (Fs) used when digitizing waveform.
     * @param Fund	    Frequency of Fundamental.
     * @param Fmin 	    Start Frequency of Range to consider in SFDR calculation.
     * @param Fmax 	    Stop Frequency of Range to consider in SFDR calculation.
     * @note		    Function returns SINAD in dB relative to Fundamental.
     * DLLAPI float SINAD(float FFT[], long lSize, float Fs, float Fund, float Fmin, float Fmax);
     */

    CCDSP_DEFINE_API(CCDSP_MANGLE_NAME, double)
    CCDSP_DEFINE_API(CCDSP_MANGLE_NAME, float)

	/*	Example
	 * 	Pure Real:
     *	CCDSP::FFT(RealData,nDataSize,pFFTData);									//dBm	default: CCDSP::_50_Ohm
     *	CCDSP::FFT(RealData,nDataSize,pFFTData,CCDSP::_0_Ohm);						//Vrms
     *	CCDSP::FFT(RealData,nDataSize,pFFTData,CCDSP::_0_Ohm,CCDSP::HANNING);		//Add Window
     *	Real + Image:
     *	CCDSP::FFT(RealData,ImageData,nDataSize,pFFTData);							//dBm	default: CCDSP::_50_Ohm
     *	CCDSP::FFT(RealData,ImageData,nDataSize,pFFTData,CCDSP::_0_Ohm);			//Vrms
     *	CCDSP::FFT(RealData,ImageData,nDataSize,pFFTData,CCDSP::_0_Ohm,true);		//fftshift  default: shift
	 *
	 */
}
#endif	/* CC_FFT_H */

