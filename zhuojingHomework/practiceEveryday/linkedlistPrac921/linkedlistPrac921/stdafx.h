// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <iostream>
#include <tchar.h>

#define SAFE_DELETE(p) {if(p) {delete p;p=0;}}
#define SAFE_DELARR(p) {if(p) {delete []p;p=0;}}

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
#include "linkedList.h"