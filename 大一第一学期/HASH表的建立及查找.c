#include "base.h"
#define KEYLENGTH 13                   /* �ؼ����ַ�������󳤶� */


typedef int ElementType; /* �ؼ����������ַ��� */
typedef int Index;                     /* ɢ�е�ַ���� */
//������
typedef struct LNode* PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******** �����ǵ�����Ķ��� ********/

typedef struct TblNode* HashTable; /* ɢ�б����� */
struct TblNode {   /* ɢ�б��㶨�� */
    int TableSize; /* �����󳤶� */
    List Heads;    /* ָ������ͷ�������� */
};

//����ɢ�б�ɢ�б�Ĵ�С���Ϊ����
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;

    /* ���·�������ͷ������� */
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    /* ��ʼ����ͷ��� */
    for (i = 0; i < H->TableSize; i++) {
        H->Heads[i].Data = i;
        H->Heads[i].Next = NULL;
    }

    return H;
}

Index Hash(ElementType Key, int TableSize)
{
    return Key % TableSize;
}

Position Find(HashTable H, ElementType Key,int* count)
{
    Position P;
    Index Pos;
    
    *count = 1;
    Pos = Hash(Key, H->TableSize); /* ��ʼɢ��λ�� */
    P = H->Heads[Pos].Next; /* �Ӹ�����ĵ�1����㿪ʼ */
    /* ��δ����β������Keyδ�ҵ�ʱ */
    while (P && P->Data != Key) {
        P = P->Next;
        (*count)++;
    }
    return P; /* ��ʱP����ָ���ҵ��Ľ�㣬����ΪNULL */
}

Status Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos,count;

    P = Find(H, Key,&count);
    if (!P) { /* �ؼ���δ�ҵ������Բ��� */
        NewCell = (Position)malloc(sizeof(struct LNode));
        NewCell->Data = Key;
        Pos = Hash(Key, H->TableSize); /* ��ʼɢ��λ�� */
        /* ��NewCell����ΪH->Heads[Pos]����ĵ�1����� */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return TRUE;
    }
    else { /* �ؼ����Ѵ��� */
        printf("��ֵ�Ѵ���\n");
        return FALSE;
    }
}

Status Delete(HashTable H, ElementType Key,int *count)
{
    Position q,p;
    Index Pos;

    *count = 1;
    Pos = Hash(Key, H->TableSize);
    q = H->Heads[Pos].Next;


    if (Key == q->Data) {
        H->Heads[Pos].Next = q->Next;
        free(q);
        return 1;
    }
    else {
        p = q->Next;
        while (p && p->Data != Key) {
            q = p;
            p = p->Next;
            (*count)++;
        }
        if (p) {
            q->Next = p->Next;
            free(p);
            return 1;
        }
        else return 0;
    }
}

void DestroyTable(HashTable H)
{
    int i;
    Position P, Tmp;

    /* �ͷ�ÿ������Ľ�� */
    for (i = 0; i < H->TableSize; i++) {
        P = H->Heads[i].Next;
        while (P) {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads); /* �ͷ�ͷ������� */
    free(H);        /* �ͷ�ɢ�б��� */
}



int main()
{
    int nums[50] = { 241,267,934,300,969,724,478,758,762,664,
        305,345,281,227,561,691,795,942,228,836,
        591,404,902,353,492,582,821,516,718,895,
        847,326,571,538,469,912,268,899,435,494,
        903,811,322,933,273,864,941,711,453,668 };
    HashTable H;
    int i,key,count;
    Position P;

    for (i = 0; i < 50; i++) {
        printf("%d",nums[i]);
        if (i % 5 == 4)printf("\n");
        else printf(",");
    }
    H = CreateTable(KEYLENGTH);
    for (i = 0; i < 50; i++)
        Insert(H, nums[i]);
    printf("������Ҫ���ҵ����֣�");
    scanf("%d", &key);
    if (P = Find(H, key, &count))printf("��ֵ�Ѵ���,���Ҵ���Ϊ:%d\n", count);
    else printf("��ֵ������\n");

    printf("������Ҫɾ�������֣�");
    scanf("%d", &key);
    if (Delete(H, key, &count))printf("��ֵ��ɾ��,���Ҵ���Ϊ:%d\n", count);
    else printf("��ֵ������\n");
    DestroyTable(H);
}