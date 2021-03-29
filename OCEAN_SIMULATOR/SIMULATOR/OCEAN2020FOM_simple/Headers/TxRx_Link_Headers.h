#pragma once
#ifndef TXRX_LINK_HEADERS_H
#define TXRX_LINK_HEADERS_H

/******************************************************************************/
/*************************** TxRxLink FUNCTIONS *******************************/
/******************************************************************************/

void StartResumeCb(DtStartResumeInteraction* StartResumeInt, void* /*usr*/)
{
	std::cout << "Start Resume Interaction Interaction from " << std::endl;
	StartResumeInt->printData();
}

void updateObject_TxRxLink_obj(DtReflectedOCEAN2020FOMTxRxLink_obj* refObj, void* /*usr*/)
{
	std::cout << "Received TxRxLink_obj Update" << std::endl;
}

void discoverObject_TxRxLink_obj(DtReflectedOCEAN2020FOMTxRxLink_obj* refObj, void* /*usr*/)
{
	/*cout<<refObj->objectId()<<endl;
	cout<<refObj->id()<<endl;
	cout<<refObj->name() << endl<<endl;*/
	//int counter = 5;
	//if (counter < 2) {
	std::cout << "Discovered new TxRxLink_obj" << std::endl;
		//std::cout << *(refObj->txRxLink_objStateRep()) << std::endl;
	refObj->addPostUpdateCallback(updateObject_TxRxLink_obj, 0);
	//	counter++;
	//}

}

void removeObject_TxRxLink_obj(DtReflectedOCEAN2020FOMTxRxLink_obj* refObj, void* /*usr*/)
{
	std::cout << "TxRxLink_obj Removed" << std::endl;
	std::cout << *(refObj->txRxLink_objStateRep()) << std::endl;
}

void TxRx_Link_OnReqInterCB(DtOCEAN2020FOMTxRx_Link_OnReqInter* inter, void* /*usr*/)
{
	std::cout << "Received TxRx_Link_OnReqInter Interaction." << std::endl;
	*inter;
}

void TxRx_Link_OffReqInterCB(DtOCEAN2020FOMTxRx_Link_OffReqInter* inter, void* /*usr*/)
{
	std::cout << "Received TxRx_Link_OffReqInter Interaction." << std::endl;
	*inter;
}

void MineEventReportInterCB(DtOCEAN2020FOMMineEventReportInter* inter, void* /*usr*/)
{
	std::cout << "Received MineEventReportInter Interaction.\n" << std::endl;
	*inter;
}

#endif