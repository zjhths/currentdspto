/**
* Copyright (c), 2015-2025
* @file fifo.c
* @brief fifo���ļ�
* @author jdh
* @verbatim
* Change Logs:
* Date           Author       Notes
* 2018-01-24     jdh          �½�
* 2018-11-06     jdh          �޸ĳ�ͨ�ø�ʽ
* @endverbatim
*/
 
 
#include "fifo.h"
 
/**
* @brief fifo�ṹ
*/
 
typedef struct
{
    int ptr_write;
    int ptr_read;
    bool is_full;
 
    // fifo�д洢��Ԫ����,�����ֽڴ�С
    int item_sum;
    // Ԫ�ش�С.��λ: �ֽ�
    int item_size;
    void *fifo_ptr;
} Fifo;
 
/**
* @brief ����fifo
* @param item_sum��fifo��Ԫ����.ע�ⲻ���ֽ���
* @param item_size: Ԫ�ش�С.��λ: �ֽ�
* @return fifo����
*/
 
void fifo_clear(int fifo_index)
{
    Fifo *fifo = (Fifo *)fifo_index;
    fifo->ptr_write = 0;
    fifo->ptr_read = 0;
    fifo->is_full = false;
}


/**
* @brief ����fifo
* @param item_sum��fifo��Ԫ����.ע�ⲻ���ֽ���
* @param item_size: Ԫ�ش�С.��λ: �ֽ�
* @return fifo����
*/

int fifo_create(int item_sum, int item_size)
{
    Fifo *fifo = (Fifo *)malloc(sizeof(Fifo));
    fifo->item_sum = item_sum;
    fifo->item_size = item_size+2;
    fifo->ptr_write = 0;
    fifo->ptr_read = 0;
    fifo->is_full = false;
    fifo->fifo_ptr = (void *)malloc(item_sum * (item_size+2));
    return (int)fifo;
}
 
/**
* @brief ɾ��fifo
* @param fifo_index: fifo����
*/
 
void fifo_delete(int fifo_index)
{
    Fifo *fifo = (Fifo *)fifo_index;
    free(fifo->fifo_ptr);
    fifo->fifo_ptr = NULL;
    free(fifo);
    fifo = NULL;
}
 
/**
* @brief fifo����Ƿ����д��
* @param fifo_index: fifo����
* @retval false:������д��.true:����д��
*/
 
bool fifo_writeable(int fifo_index)
{	
    Fifo *fifo = (Fifo *)fifo_index;
    return !fifo->is_full;
}
 
/**
* @brief fifoд��
* @param fifo_index: fifo����
* @param frame:д��Ԫ��ָ��
* @return false:ʧ��.true:�ɹ�
*/
 
bool fifo_write(int fifo_index, void *data,unsigned short *data_len)
{
    Fifo *fifo = (Fifo *)fifo_index;
    if (fifo->is_full)
	{
		return false;
	}
    memcpy((char *)(fifo->fifo_ptr) + fifo->ptr_write * fifo->item_size, data_len, 2);
    memcpy((char *)(fifo->fifo_ptr) + fifo->ptr_write * fifo->item_size+2, data, fifo->item_size-2);
    fifo->ptr_write++;
 
    if (fifo->ptr_write >= fifo->item_sum)
	{
        fifo->ptr_write = 0;
	}
    if (fifo->ptr_write == fifo->ptr_read)
	{
        fifo->is_full = true;
	}
	
	return true;
}
 
/**
* @brief fifo����д��
* @param fifo_index: fifo����
* @param data: д��Ԫ��ָ��
* @param item_num��д���Ԫ����Ŀ
* @return false:ʧ��.true:�ɹ�
*/
 
bool fifo_write_batch(int fifo_index, void *data, int item_num)
{
    Fifo *fifo = (Fifo *)fifo_index;
    if (fifo_writeable_item_count((int)fifo) < item_num)
    {
        return false;
    }
 
    memcpy((char *)(fifo->fifo_ptr) + fifo->ptr_write * fifo->item_size, data, fifo->item_size * item_num);
    fifo->ptr_write += item_num;
 
    if (fifo->ptr_write >= fifo->item_sum)
    {
        fifo->ptr_write = 0;
    }
    if (fifo->ptr_write == fifo->ptr_read)
    {
        fifo->is_full = true;
    }
 
    return true;
}
 
/**
* @brief fifo����Ƿ���Զ�ȡ
* @param fifo_index: fifo����
* @return false:�����Զ�ȡ.true:���Զ�ȡ
*/
 
bool fifo_readable(int fifo_index)
{
    Fifo *fifo = (Fifo *)fifo_index;
    if (fifo->ptr_write == fifo->ptr_read && !fifo->is_full)
	{
		return false;
	}
	return true;
}
 
/**
* @brief fifo��ȡ
* @param fifo_index: fifo����
* @param data: ��ȡ������
* @return false: ʧ��.true: �ɹ�
*/
 
bool fifo_read(int fifo_index, void *data,unsigned short *data_len)
{
    Fifo *fifo = (Fifo *)fifo_index;
    if (fifo->ptr_write == fifo->ptr_read && !fifo->is_full)
	{
		return false;
	}
    memcpy(data_len, (char *)(fifo->fifo_ptr) + fifo->ptr_read * fifo->item_size, 2);
    memcpy(data, (char *)(fifo->fifo_ptr) + fifo->ptr_read * fifo->item_size+2, fifo->item_size-2);
    fifo->ptr_read++;
    if (fifo->ptr_read >= fifo->item_sum)
	{
        fifo->ptr_read = 0;
	}
    fifo->is_full = false;
	return true;
}
 
/**
* @brief fifo������ȡ
* @param fifo_index: fifo����
* @param data: ��ȡ������
* @param item_num����ȡ��Ԫ����
* @return false: ʧ��.true: �ɹ�
*/
 
bool fifo_read_batch(int fifo_index, void *data, int item_num)
{
    Fifo *fifo = (Fifo *)fifo_index;
    if (fifo_readable_item_count((int)fifo) < item_num)
    {
        return false;
    }
 
    memcpy(data, (char *)(fifo->fifo_ptr) + fifo->ptr_read * fifo->item_size, fifo->item_size * item_num);
    fifo->ptr_read += item_num;
    if (fifo->ptr_read >= fifo->item_sum)
    {
        fifo->ptr_read = 0;
    }
    fifo->is_full = false;
    return true;
}
 
/**
* @brief fifo�ɶ���Ԫ����
* @param fifo_index: fifo����
* @return Ԫ����
*/
 
int fifo_readable_item_count(int fifo_index)
{
    Fifo *fifo = (Fifo *)fifo_index;
    if (fifo->is_full)
    {
        return fifo->item_sum;
    }
    else
    {
        return (fifo->item_sum + fifo->ptr_write - fifo->ptr_read) % fifo->item_sum;
    }
}
 
/**
* @brief fifo��д��Ԫ����
* @param fifo_index: fifo����
* @return Ԫ����
*/
 
int fifo_writeable_item_count(int fifo_index)
{
    Fifo *fifo = (Fifo *)fifo_index;
    if (fifo->is_full)
    {
        return 0;
    }
    else
    {
        if (fifo->ptr_write == fifo->ptr_read)
        {
            return fifo->item_sum;
        }
        else
        {
            return (fifo->item_sum + fifo->ptr_read - fifo->ptr_write) % fifo->item_sum;
        }
    }
}
