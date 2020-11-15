#include <stdio.h>
#include "norm.h"
#include <math.h>
#include <pthread.h>


float norm(float *U, int n)
{
    float norm_ = 0;
    for(int i = 0;i<n;i++)
    {
        norm_ += sqrt(fabsf(U[i]));
    }
    return norm_;
}

float norm_vector(float *U, int n)
{

	float norm_ = 0;
	__m256 mm_unit, mm_sum;
	int nBlockWidth = 8;//__m256 has 256 bits divide by float lenght which is 32 bits
	int cntBlock = n/nBlockWidth;// with once calcute 8 floats, cntBlock times can finish the calculation of U
    mm_sum = _mm256_setr_ps(0,0,0,0,0,0,0,0);//ps for float, pd for double
    for (int i = 0; i <n; i+= 8)
    {
    	mm_unit = _mm256_loadu_ps(&U[i]);  //load data from U to the vector
    	mm_sum = _mm256_add_ps(mm_s,mm_p);
    }

    float Vec[nBlockWidth]; 
    //load data in vector mm_s to the array Vec
	_mm256_storeu_ps(&Vec[0],mm_sum);
	for (i = 0; i < nBlockWidth; i ++)
	{
		norm_ += Vec[i];
	}
	return norm_;

}

int main()
{
    float a[5] = {1.2,-2.3,3.4,4.5,5.5};
    printf("answer is %f\n",norm(a,5));
    return 0;
}