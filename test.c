#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "itcast_asn1_der.h"

//结构体声明
typedef struct _teacher_t
{
	char name[32];
	int age;
	char *p;
	int pLen;
}teacher_t;

//写文件
int writeFile(unsigned char *inData, int inDataLen)
{
	FILE *fp = NULL;
	//1. 打开文件
	fp = fopen("D:/teacher.ber", "w");
	if (NULL == fp)
	{
		printf("打开文件失败....\n");
		return -1;
	}

	//2. 写文件
	fwrite(inData, sizeof(char), inDataLen, fp);

	//3. 关闭文件
	fclose(fp);

	return 0;
}



//简单结构体编码
int TeacherEncode(const teacher_t *t, unsigned char **outData, int *outDataLen)
{
	ITCAST_INT ret = -1;

	ITCAST_ANYBUF *head = NULL;
	ITCAST_ANYBUF *tmpNode = NULL;
	ITCAST_ANYBUF *tmpNameNode = NULL;
	ITCAST_ANYBUF *outDataNode = NULL;

	//传出
	unsigned char *out = NULL;

	//1. 参数检查
	if (NULL == t || NULL == outData || NULL == outDataLen)
	{
		printf("参数非法...\n");
		return -1;
	}

	//2. 编码name
	//将char*转化为ANYBUF类型
	ret = DER_ITCAST_String_To_AnyBuf(&tmpNameNode, (unsigned char *)t->name, strlen(t->name));  //1.free
	if (0 != ret)
	{
		printf("DER_ITCAST_String_To_AnyBuf failed...\n");
		goto err0;

	}

	ret = DER_ItAsn1_WritePrintableString(tmpNameNode, &head); //2.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_WritePrintableString failed...\n");
		goto err0;
	}

	//3. 编码age
	tmpNode = head;
	ret = DER_ItAsn1_WriteInteger(t->age, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed...\n");
		goto err0;
	}

	//4. 编码p
	tmpNode = tmpNode->next;
	ret = EncodeChar(t->p, strlen(t->p), &(tmpNode->next));
	if (0 != ret)
	{
		printf("EncodeChar failed...\n");
		goto err0;
	}

	//5. 编码pLen
	tmpNode = tmpNode->next;
	ret = DER_ItAsn1_WriteInteger(t->pLen, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed...\n");
		goto err0;
	}

	//6. 编码结构体
	ret = DER_ItAsn1_WriteSequence(head, &outDataNode); //3.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteSequence failed...\n");
		goto err0;
	}

	//7. 传出
	out = malloc(outDataNode->dataLen + 1);
	if (NULL == out)
	{
		printf("malloc failed..\n");
		goto err0;
	}
	memset(out, 0, outDataNode->dataLen + 1);

	//拷贝数据
	memcpy(out, outDataNode->pData, outDataNode->dataLen);
	*outData = out;
	*outDataLen = outDataNode->dataLen;

	//8. 释放内存  valgrind 
	if (NULL != tmpNameNode)
	{
		DER_ITCAST_FreeQueue(tmpNameNode);
	}

	if (NULL != head)
	{
		DER_ITCAST_FreeQueue(head);
	}

	if (NULL != outDataNode)
	{
		DER_ITCAST_FreeQueue(outDataNode);
	}

	return 0;
err0:
	if (NULL != tmpNameNode)
	{
		DER_ITCAST_FreeQueue(tmpNameNode);
	}

	if (NULL != head)
	{
		DER_ITCAST_FreeQueue(head);
	}

	if (NULL != outDataNode)
	{
		DER_ITCAST_FreeQueue(outDataNode);
	}

	return -1;
}

//简单结构体解码
int TeacherDecode(const unsigned char *inData, int inDataLen, teacher_t **pTeacher)
{

	return 0;
}

//简单结构体内存释放
int TeacherFreeMem(teacher_t **t)
{
	return 0;
}

int main()
{
	int ret = 0;

	//传入参数
	unsigned char *outData = NULL;
	int outDataLen = 0;

	//传出参数
	teacher_t *pT = NULL;


	//结构体变量定义和初始化
	teacher_t teacher = {
		.name = "kitty",
		.age = 18,
		.p = "hello itcast",
		.pLen = strlen("hello itcast")
	};

	//1. 编码
	ret = TeacherEncode(&teacher, &outData, &outDataLen);
	if (0 != ret)
	{
		printf("TeacherEncode failed...\n");
		return 1;
	}
	printf("简单结构体编码成功...\n");

	printf("outData: %s outDataLen: %d\n", outData, outDataLen);
	//写文件
	writeFile(outData, outDataLen);

#if 0
	//2. 解码
	ret = TeacherDecode(outData, outDataLen, &pT);
	if (0 != ret)
	{
		printf("TeacherDecode failed...\n");
		return 1;
	}
	printf("简单结构体解码成功....\n");

	//3. 判断
	if ((teacher.age == pT->age) && (strcmp(teacher.name, pT->name) == 0))
	{
		printf("简单结构体编解码一致...\n");
	}
	else
	{
		printf("简单结构体编解码不一致...\n");
	}

	printf("name: %s age:%d p: %s pLen: %d\n", pT->name, pT->age, pT->p, pT->pLen);

	//4. 释放内存
	free(outData);
	TeacherFreeMem(&pT);
#endif
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");
	printf("hello world\n");

	system("pause");
	return 0;
}
