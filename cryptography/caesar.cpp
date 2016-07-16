#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// 凯撒密码实现
// 将明文字母变为它后面的三个字母，后面的循环到前面
// 公式 f(a) = (f(a) + 3) % 26 
int main(int argc, char** argv) {
	char P[128];	
	char C[128];	
	memset(P, 0, sizeof(P));
	memset(C, 0, sizeof(C));
	int K = 3;
	printf("please input plaintext:\n");/// 输入明文
	fgets(P, sizeof(P), stdin);

	for (int i = 0; P[i] != '\0'; ++i) { /// 逐个加密
		if (P[i] >= 'a' && P[i] <= 'z') { /// 小写字母
			C[i] = (P[i] - 'a'+ K ) % 26 + 'a';
		}
		else if (P[i] >= 'A' && P[i] <= 'Z') { /// 大写字母
			C[i] = (P[i] - 'A'+ K ) % 26 + 'A';
		}
		else { /// 其它转换成空格
			C[i] = ' ';
		}
	}

	printf("the ciphertext is \n%s\n", C); /// 输出密文
	return 0;
}
