/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Portions Copyright (C) 2000 Relatable
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

   $Id$

----------------------------------------------------------------------------*/

#include "trm.h"
#include "sigfft.h"
#include "sigclient.h"
#include "uuid.h"

#include <stdio.h>
#include <stdlib.h>

const int iFFTPoints = 32;
const int iNumSamplesNeeded = 288000;

TRM::TRM(void)
{
    m_downmixBuffer = NULL;
    m_storeBuffer = NULL;
}

TRM::~TRM(void)
{
}

bool TRM::SetProxy(const string &proxyAddr, short proxyPort)
{
    m_proxy = proxyAddr;
    m_proxyPort = proxyPort;

    return true;
}

void TRM::SetPCMDataInfo(int samplesPerSecond, int numChannels,
                         int bitsPerSample)
{
    m_samples_per_second = samplesPerSecond;
    m_number_of_channels = numChannels;
    m_bits_per_sample = bitsPerSample;

    if (m_downmixBuffer) {
        delete [] m_downmixBuffer;
        m_downmixBuffer = NULL;
    }
    if (m_storeBuffer) {
        delete [] m_storeBuffer;
        m_storeBuffer = NULL;
    }
    m_numSamplesWritten = 0;

    float mult = (float)m_samples_per_second / 11025.0;
    mult *= (m_bits_per_sample / 8);
    mult *= (m_number_of_channels);
    mult = ceil(mult);

    m_numRealSamplesWritten = 0;
    m_numRealSamplesNeeded = iNumSamplesNeeded * (int)mult;
    m_storeBuffer = new char[m_numRealSamplesNeeded + 20];
}

bool TRM::GenerateSignature(char *data, int size, string &strGUID,
                            string &collID)
{
   if (m_numRealSamplesWritten < m_numRealSamplesNeeded) {
       int i = 0;
       while (i < size && m_numRealSamplesWritten < m_numRealSamplesNeeded) {
           m_storeBuffer[m_numRealSamplesWritten] = data[i];
           m_numRealSamplesWritten++;
           i++;
       }
   }

   if (m_numRealSamplesWritten < m_numRealSamplesNeeded)
       return false;

   GenerateSignatureNow(strGUID, collID);

   return true;

}

void TRM::DownmixPCM(void)
{
   // DC Offset fix
   long int lsum = 0, rsum = 0;
   long int numsamps = 0;
   int lDC = 0, rDC = 0;
   signed short lsample, rsample;
   unsigned char ls;
   int readpos = 0;
   
   if (m_bits_per_sample == 16) {
       if (m_number_of_channels == 2) {
           while (readpos < (m_numRealSamplesWritten / 2)) {
               lsample = ((signed short *)m_storeBuffer)[readpos++];
               rsample = ((signed short *)m_storeBuffer)[readpos++];
               
               lsum += lsample; 
               rsum += rsample;
               numsamps++;
           }
           lDC = -(lsum / numsamps);
           rDC = -(rsum / numsamps);

           readpos = 0;
           while (readpos < (m_numRealSamplesWritten / 2)) {
               ((signed short *)m_storeBuffer)[readpos] = 
                    ((signed short *)m_storeBuffer)[readpos] + lDC;
               readpos++;
               ((signed short *)m_storeBuffer)[readpos] =
                    ((signed short *)m_storeBuffer)[readpos] + rDC;
               readpos++;
           }
       }
       else {
           while (readpos < m_numRealSamplesWritten / 2) {
               lsample = ((signed short *)m_storeBuffer)[readpos++];
               
               lsum += lsample;
               numsamps++;
           }

           lDC = -(lsum / numsamps);
 
           readpos = 0;
           while (readpos < m_numRealSamplesWritten / 2) {
               ((signed short *)m_storeBuffer)[readpos] =
                    ((signed short *)m_storeBuffer)[readpos] + lDC;
               readpos++;
           }
       }
    }
    else {
       if (m_number_of_channels == 2) {
           while (readpos < (m_numRealSamplesWritten)) {
               lsample = ((char *)m_storeBuffer)[readpos++];
               rsample = ((char *)m_storeBuffer)[readpos++];

               lsum += lsample;
               rsum += rsample;
               numsamps++;
           }
           lDC = -(lsum / numsamps);
           rDC = -(rsum / numsamps);

           readpos = 0;
           while (readpos < (m_numRealSamplesWritten)) {
               ((char *)m_storeBuffer)[readpos] =
                    ((char *)m_storeBuffer)[readpos] + lDC;
               readpos++;
               ((char *)m_storeBuffer)[readpos] =
                    ((char *)m_storeBuffer)[readpos] + rDC;
               readpos++;
           }
       }
       else {
           while (readpos < m_numRealSamplesWritten / 2) {
               lsample = ((char *)m_storeBuffer)[readpos++];

               lsum += lsample;
               numsamps++;
           }

           lDC = -(lsum / numsamps);

           readpos = 0;
           while (readpos < m_numRealSamplesWritten / 2) {
               ((char *)m_storeBuffer)[readpos] =
                    ((char *)m_storeBuffer)[readpos] + lDC;
               readpos++;
           }
       }
    }

   if (!m_downmixBuffer)
       m_downmixBuffer = new unsigned char[iNumSamplesNeeded];

   m_downmix_size = m_numRealSamplesWritten;

   if (m_samples_per_second != 11025)
       m_downmix_size = (int)((float)m_downmix_size * 
                            (11025.0 / (float)m_samples_per_second));

   if (m_bits_per_sample != 8)
       m_downmix_size /= 2;

   if (m_number_of_channels != 1)
       m_downmix_size /= 2;

   int maxwrite = m_downmix_size;
   int writepos = 0;
   float rate_change = m_samples_per_second / 11025.0;

   if (m_bits_per_sample == 16) {
       unsigned char *tempbuf = new unsigned char[m_numRealSamplesWritten / 2];
       readpos = 0;
       while (readpos < m_numRealSamplesWritten / 2) {
          long int samp = ((signed short *)m_storeBuffer)[readpos];

          samp /= 256;

          if (samp >= CHAR_MAX)
              samp = CHAR_MAX;
          else if (samp <= CHAR_MIN)
              samp = CHAR_MIN;

          samp ^= 128;

          tempbuf[readpos] = samp;
          readpos++;
      }
 
      delete [] m_storeBuffer;
      m_numRealSamplesWritten /= 2;
      m_storeBuffer = (char *)tempbuf;

      m_bits_per_sample = 8;
   }

   if (m_number_of_channels == 2) {
       unsigned char *tempbuf = new unsigned char[m_numRealSamplesWritten / 2];
       readpos = 0;
       writepos = 0;
       while (writepos < m_numRealSamplesWritten / 2) {
          unsigned char ls = ((unsigned char *)m_storeBuffer)[readpos++];
          unsigned char rs = ((unsigned char *)m_storeBuffer)[readpos++];

          tempbuf[writepos] = (ls + rs) / 2;
          writepos++;
      }

      delete [] m_storeBuffer;
      m_numRealSamplesWritten /= 2;
      m_storeBuffer = (char *)tempbuf;

      m_number_of_channels = 1;
   }

   writepos = 0;
   while ((writepos < maxwrite) &&
          (m_numSamplesWritten < iNumSamplesNeeded))
   {
       readpos = (int)((float)writepos * rate_change);
       
       ls = ((unsigned char *)m_storeBuffer)[readpos++];

       m_downmixBuffer[m_numSamplesWritten] = ls;
       m_numSamplesWritten++;
       writepos++;
   }

   delete [] m_storeBuffer;
   m_storeBuffer = NULL;
}

void TRM::GenerateSignatureNow(string &strGUID, string &collID)
{
    DownmixPCM();

#ifdef TRM_DEBUG
    FILE *blah = fopen("/tmp/test.raw", "w+");
    fwrite(m_downmixBuffer, m_numSamplesWritten, sizeof(unsigned char), blah);
    fclose(blah);
#endif

    char *sample = (char *)m_downmixBuffer;  
    bool bLastNeg = false;
    if (*sample <= 0)
          bLastNeg = true;

    FFT *pFFT = new FFT(iFFTPoints, 11025);
    pFFT->CopyIn((char *)m_downmixBuffer, iFFTPoints);
    pFFT->Transform();

    char *pCurrent = (char *)m_downmixBuffer;
    char *pBegin = pCurrent;
    int iFFTs = m_numSamplesWritten / iFFTPoints;
    int j, k;

    int iSpectrum[iFFTPoints];
    for (j = 0; j < iFFTPoints; j++)
        iSpectrum[j] = 0;

    int iZeroCrossings = 0;
    double dEnergySum = 0.0;
    int iFinishedFFTs = 0;

    for (j = 0; j < iFFTs; j++, iFinishedFFTs++) {
        pFFT->CopyIn(pCurrent, iFFTPoints);
        pFFT->Transform();

        for (k = 0; k < iFFTPoints; k++)
            iSpectrum[k] += (int)pFFT->GetIntensity(k);
        
        while (pCurrent < pBegin + iFFTPoints)
        {
            dEnergySum += ((*pCurrent) * (*pCurrent));
             
            if (bLastNeg && (*pCurrent > 0))
            {
                bLastNeg = false;
                iZeroCrossings++;
            }
            else if (!bLastNeg && (*pCurrent <= 0))
                bLastNeg = true;
            pCurrent++;
        }
        pBegin = pCurrent;
    }

    float fLength = m_numSamplesWritten / (float)11025;
    float fAverageZeroCrossing = iZeroCrossings / fLength;
    float fEnergy = dEnergySum / (float)m_numSamplesWritten;
    for (int i = 0; i < iFFTPoints; i++)
        iSpectrum[i] = iSpectrum[i] / iFinishedFFTs;

#ifdef TRM_DEBUG
    cout << fEnergy << " " << fAverageZeroCrossing << endl;
    for (int j = 0; j < 32; j++)
        cout << iSpectrum[j] << endl;
#endif

    AudioSig *signature = new AudioSig(fEnergy, fAverageZeroCrossing,
                                       fLength, iSpectrum); 

    SigClient *sigClient = new SigClient();
    sigClient->SetAddress("209.249.187.199", 4445);
    sigClient->SetProxy(m_proxy, m_proxyPort);

    if (collID == "")
        collID = "EMPTY_COLLECTION";

    sigClient->GetSignature(signature, strGUID, collID);

    delete pFFT;
    delete signature;
    delete sigClient;

    delete [] m_downmixBuffer;
    m_downmixBuffer = 0;
    m_numSamplesWritten = 0;
}

void TRM::ConvertSigToASCII(char sig[17], char ascii_sig[37])
{
    uuid_ascii((unsigned char *)sig, ascii_sig);
}

