
#ifndef _FIFO_H_
#define _FIFO_H_
 
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "stdbool.h"
#include "string.h"
#include "math.h"
 
/**
* @brief ����fifo
* @param item_sum��fifo��Ԫ����.ע�ⲻ���ֽ���
* @param item_size: Ԫ�ش�С.��λ: �ֽ�
* @return fifo����
*/
 
int fifo_create(int item_sum, int item_size);
 
/**
* @brief ɾ��fifo
* @param fifo_index: fifo����
*/
 
void fifo_delete(int fifo_index);
 
/**
* @brief fifo����Ƿ����д��
* @param fifo_index: fifo����
* @retval false:������д��.true:����д��
*/
 
bool fifo_writeable(int fifo_index);
 
/**
* @brief fifoд��
* @param fifo_index: fifo����
* @param frame:д��Ԫ��ָ��
* @return false:ʧ��.true:�ɹ�
*/
 
bool fifo_write(int fifo_index, void *data);
 
/**
* @brief fifo����д��
* @param fifo_index: fifo����
* @param data: д��Ԫ��ָ��
* @param @param item_num��д���Ԫ����Ŀ
* @return false:ʧ��.true:�ɹ�
*/
 
bool fifo_write_batch(int fifo_index, void *data, int item_num);
 
/**
* @brief fifo����Ƿ���Զ�ȡ
* @param fifo_index: fifo����
* @return false:�����Զ�ȡ.true:���Զ�ȡ
*/
 
bool fifo_readable(int fifo_index);
 
/**
* @brief fifo��ȡ
* @param fifo_index: fifo����
* @param data: ��ȡ������
* @return false: ʧ��.true: �ɹ�
*/
 
bool fifo_read(int fifo_index, void *data);
 
/**
* @brief fifo������ȡ
* @param fifo_index: fifo����
* @param data: ��ȡ������
* @param item_num����ȡ��Ԫ����
* @return false: ʧ��.true: �ɹ�
*/
 
bool fifo_read_batch(int fifo_index, void *data, int item_num);
 
/**
* @brief fifo�ɶ���Ԫ����
* @param fifo_index: fifo����
* @return Ԫ����
*/
 
int fifo_readable_item_count(int fifo_index);
 
/**
* @brief fifo��д��Ԫ����
* @param fifo_index: fifo����
* @return Ԫ����
*/
 
int fifo_writeable_item_count(int fifo_index);
 
#endif
