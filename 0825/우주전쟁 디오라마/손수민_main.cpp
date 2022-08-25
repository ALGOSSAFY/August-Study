#include <iostream>
#include <vector>

using namespace std;
/*
  우주 전쟁 디오라마
  N개 종류 부품 K개 필요
  용돈에 맞게
  만들수 있는 우주선 최대 모델 개수
  파라메트릭
  우주선 만들 수 있는 최대개수 100000
  부품수
  무조건 가성비 좋은걸로 살 수 가 없음
  일단 1 ~100000 에서 우주선의 갯수 mid개로 결정
  mid개로 결정해서 만들 수 있나 체크 필요
  우주선의 수 -> 파라메트릭
  적절한 금액 -> 파라메트릭
  => sk의 수, bk의 수 파라메트릭?

*/
int n, m;
struct info
{
    int k;
    int x;
    int sk;
    int sp;
    int bk;
    int bp;
};
vector<info>arr(100);

bool if_possible(int comp)
{
    int init_money = m;
    //sk와 bk가 있어서 애매함
    //sk와 bk 적절하게 합쳐야함
    //각 부품마다 sk bk 수?
    //해당 comp를 채우기 위한 sk와 bk의 수
    //money가 음수면 바로 false
    for (int i = 0; i < n; i++)
    {
        info now = arr[i];
        int first_money = 0;
        //이미 만들 수 있을 수도 있음
        int last_money = init_money;
        int k_needed = now.k * comp;
        k_needed -= now.x;
        if (k_needed == 0)
            continue;
        //못만들면 큰값으로 빼서 -> 못만든다
            int spent = 123456;
            int sk_left = 0;
            int sk_right = k_needed / now.sk;
            if (k_needed % now.sk != 0)
                sk_right++;
            for (int sk = sk_left; sk <= sk_right; sk++)
            {
                int tmp_money;
                tmp_money = sk * now.sp;
                int now_needed = k_needed;
                now_needed -= now.sk * sk;
                if (now_needed <= 0)
                {
                  spent = min(spent, tmp_money);
                }
                else if (now_needed > 0)
                {
                    int bk_needed = now_needed / now.bk;
                    if (now_needed % now.bk)
                        bk_needed++;
                    tmp_money += now.bp * bk_needed;
                    spent = min(tmp_money, spent);
                }




            }
          //그냥 가장 싸게 살 수 있는 방법으로 삼 




        init_money -= spent;
        if (init_money < 0)
            return false;

    }
    return true;

}



int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int k, x, sk, sp, bk, bp;
        cin >> k >> x >> sk >> sp >> bk >> bp;
        arr[i] = { k,x,sk,sp,bk,bp };


    }
    int left = 0;
    int right = 100000;
    int poss = 0;
    //if_possible(3);

    while (left <= right)
    {
        int mid = (left + right) / 2;
        //mid개 만들 수 있나 결정
        //못만들면 줄이고
        //만들면 늘리자
        //만드는것 어떻게 결정?
        //N개의 부품이 필요함
        //부품마다 이진?
        if (if_possible(mid))
        {
            left = mid + 1;
            poss = mid;
        }
        else
        {
            right = mid - 1;
        }


    }

    cout << poss;

}
