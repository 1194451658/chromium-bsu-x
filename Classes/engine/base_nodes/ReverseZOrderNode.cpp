
#include "ReverseZOrderNode.h"


 void ReverseZOrderNode::sortAllChildren()
{
	CCNode::sortAllChildren();

	// reverse order
	int length = m_pChildren->data->num;

	for(int i=0; i<length/2.0; i++)
	{
		CCObject* temp = m_pChildren->data->arr[length-1-i];
		m_pChildren->data->arr[length-1-i] = m_pChildren->data->arr[i];
		m_pChildren->data->arr[i] = temp;
	}
}