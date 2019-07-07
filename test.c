#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "itcast_asn1_der.h"

//�ṹ������
typedef struct _teacher_t
{
	char name[32];
	int age;
	char *p;
	int pLen;
}teacher_t;

//д�ļ�
int writeFile(unsigned char *inData, int inDataLen)
{
	FILE *fp = NULL;
	//1. ���ļ�
	fp = fopen("D:/teacher.ber", "w");
	if (NULL == fp)
	{
		printf("���ļ�ʧ��....\n");
		return -1;
	}

	//2. д�ļ�
	fwrite(inData, sizeof(char), inDataLen, fp);

	//3. �ر��ļ�
	fclose(fp);

	return 0;
}



//�򵥽ṹ�����
int TeacherEncode(const teacher_t *t, unsigned char **outData, int *outDataLen)
{
	ITCAST_INT ret = -1;

	ITCAST_ANYBUF *head = NULL;
	ITCAST_ANYBUF *tmpNode = NULL;
	ITCAST_ANYBUF *tmpNameNode = NULL;
	ITCAST_ANYBUF *outDataNode = NULL;

	//����
	unsigned char *out = NULL;

	//1. �������
	if (NULL == t || NULL == outData || NULL == outDataLen)
	{
		printf("�����Ƿ�...\n");
		return -1;
	}

	//2. ����name
	//��char*ת��ΪANYBUF����
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

	//3. ����age
	tmpNode = head;
	ret = DER_ItAsn1_WriteInteger(t->age, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed...\n");
		goto err0;
	}

	//4. ����p
	tmpNode = tmpNode->next;
	ret = EncodeChar(t->p, strlen(t->p), &(tmpNode->next));
	if (0 != ret)
	{
		printf("EncodeChar failed...\n");
		goto err0;
	}

	//5. ����pLen
	tmpNode = tmpNode->next;
	ret = DER_ItAsn1_WriteInteger(t->pLen, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed...\n");
		goto err0;
	}

	//6. ����ṹ��
	ret = DER_ItAsn1_WriteSequence(head, &outDataNode); //3.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteSequence failed...\n");
		goto err0;
	}

	//7. ����
	out = malloc(outDataNode->dataLen + 1);
	if (NULL == out)
	{
		printf("malloc failed..\n");
		goto err0;
	}
	memset(out, 0, outDataNode->dataLen + 1);

	//��������
	memcpy(out, outDataNode->pData, outDataNode->dataLen);
	*outData = out;
	*outDataLen = outDataNode->dataLen;

	//8. �ͷ��ڴ�  valgrind 
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

//�򵥽ṹ�����
int TeacherDecode(const unsigned char *inData, int inDataLen, teacher_t **pTeacher)
{

	return 0;
}

//�򵥽ṹ���ڴ��ͷ�
int TeacherFreeMem(teacher_t **t)
{
	return 0;
}

int main()
{
	int ret = 0;

	//�������
	unsigned char *outData = NULL;
	int outDataLen = 0;

	//��������
	teacher_t *pT = NULL;


	//�ṹ���������ͳ�ʼ��
	teacher_t teacher = {
		.name = "kitty",
		.age = 18,
		.p = "hello itcast",
		.pLen = strlen("hello itcast")
	};

	//1. ����
	ret = TeacherEncode(&teacher, &outData, &outDataLen);
	if (0 != ret)
	{
		printf("TeacherEncode failed...\n");
		return 1;
	}
	printf("�򵥽ṹ�����ɹ�...\n");

	printf("outData: %s outDataLen: %d\n", outData, outDataLen);
	//д�ļ�
	writeFile(outData, outDataLen);

#if 0
	//2. ����
	ret = TeacherDecode(outData, outDataLen, &pT);
	if (0 != ret)
	{
		printf("TeacherDecode failed...\n");
		return 1;
	}
	printf("�򵥽ṹ�����ɹ�....\n");

	//3. �ж�
	if ((teacher.age == pT->age) && (strcmp(teacher.name, pT->name) == 0))
	{
		printf("�򵥽ṹ������һ��...\n");
	}
	else
	{
		printf("�򵥽ṹ�����벻һ��...\n");
	}

	printf("name: %s age:%d p: %s pLen: %d\n", pT->name, pT->age, pT->p, pT->pLen);

	//4. �ͷ��ڴ�
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
