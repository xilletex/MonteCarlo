#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define SRAND_REDEF 100000
#define RND_MIN 0
#define RND_MAX 1

static int float_rand_seed_flag = 0;
float maybe_pi = 0;

float FlortGetRandom(float min, float max)
{
    float ret_value;
    if (float_rand_seed_flag == 0) {
        srand((unsigned int)time(NULL));
        float_rand_seed_flag = 1;
    }
    ret_value = min + (max-min)*((float)rand()/RAND_MAX);
    return ret_value;
}

void main(void){
	/* main内で使用するauto変数の定義 */
	unsigned long long i = 0;
	float throw_x;
	float throw_y;
	float distance;

	double debug_reg = 0;
	debug_reg = i / 100;

	unsigned long long count = 0;	/* 試行回数 */
	unsigned long long incircle = 0;	/* 円の中に入った回数 */
	int win = 0;
	double win_num = 0;
  printf("Input LOOP number。：");
  scanf("%lf", &i);
  if(i <= 100){
  debug_reg = 1;
  }
  else if (i >= 100000000){
    debug_reg = 10000000;
  }
printf("\n");
  do{
	count++;

  if((count % SRAND_REDEF)==0)
  {
    float_rand_seed_flag = 0;
  }
    throw_x = FlortGetRandom(RND_MIN, RND_MAX); //x座標
    throw_y = FlortGetRandom(RND_MIN, RND_MAX); //y座標
	distance = sqrt (  (throw_x * throw_x) + (throw_y * throw_y)  );
	if (distance <= 1.0)
	{
		incircle++;
	}else
	{
		;
	}

	/* 推定円周率を更新 */
	maybe_pi = (4*((float)incircle / (float)count));

	/* ループ中の表示 */
  if(fmod(count, debug_reg)==0){
    printf("%d回試行を行い、円のなか%d回なので、推定円周率は %.15f %%です。\n", count , incircle, maybe_pi);
    printf("throw_x:%10lu, throw_y:%10lu, maybe_pi:%10lu\n",throw_x, throw_y, maybe_pi );
      usleep(10000);
  }

  }while(count != i);
  printf("\n%d回試行を行い、円内に入ったのが%d回なので、推定円周率は %.15f %%です。\n", count , incircle, maybe_pi);
}
