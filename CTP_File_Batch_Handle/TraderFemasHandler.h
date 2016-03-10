#pragma once
#include "FemasTHelper.h"
#include "ThostFtdcTraderApi.h"
#include "FemasSpiMessage.h"

class CFemasTraderSpiHandler
	: public CThostFtdcTraderSpi
{
public:
	CFemasTHelper* m_pApiWrapper;
	CFemasTraderSpiHandler(CFemasTHelper * ThostApiPlus)
		:m_pApiWrapper(ThostApiPlus)
	{

	}
	void AddMsg(CThostSpiMessage * SpiMsg)
	{
		m_pApiWrapper->AddSpiMsg(this, SpiMsg);
	}

	/////当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	//virtual void OnFrontConnected()
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnFrontConnected, (int *)NULL));
	//};

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	//virtual void OnFrontDisconnected(int nReason)
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnFrontDisconnected, &nReason));
	//};
	//
	/////心跳超时警告。当长时间未收到报文时，该方法被调用。
	/////@param nTimeLapse 距离上次接收报文的时间
	//virtual void OnHeartBeatWarning(int nTimeLapse)
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnHeartBeatWarning, &nTimeLapse));
	//};
	//
	/////报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	/////@param nTopicID 主题代码（如私有流、公共流、行情流等）
	/////@param nSequenceNo 报文序号
	//virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	//
	/////报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	/////@param nTopicID 主题代码（如私有流、公共流、行情流等）
	/////@param nSequenceNo 报文序号
	//virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};
	//
	//
	/////错误应答
	//virtual void OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnRspError, (ThostFtdcRspInfoField*)pRspInfo, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
	//};
	//
	/////风控前置系统用户登录应答
	//virtual void OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnRspUserLogin, pRspUserLogin, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
	//};
	//
	/////用户退出应答
	//virtual void OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////用户密码修改应答
	//virtual void OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////报单录入应答
	//virtual void OnRspOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnRspOrderInsert, pInputOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
	//};
	//
	/////报单操作应答
	//virtual void OnRspOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////数据流回退通知
	//virtual void OnRtnFlowMessageCancel(CUstpFtdcFlowMessageCancelField *pFlowMessageCancel) {};
	//
	/////成交回报
	//virtual void OnRtnTrade(CUstpFtdcTradeField *pTrade)
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnRtnTrade, pTrade));
	//};
	//
	/////报单回报
	//virtual void OnRtnOrder(CUstpFtdcOrderField *pOrder)
	//{
	//	AddMsg(new CThostSpiMessage(SPI::OnRtnOrder, pOrder));
	//};
	//
	/////报单录入错误回报
	//virtual void OnErrRtnOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo) {};
	//
	/////报单操作错误回报
	//virtual void OnErrRtnOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo) {};
	//
	/////合约交易状态通知
	//virtual void OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus) {};
	//
	/////报单查询应答
	//virtual void OnRspQryOrder(CUstpFtdcOrderField *pOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////成交单查询应答
	//virtual void OnRspQryTrade(CUstpFtdcTradeField *pTrade, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////可用投资者账户查询应答
	//virtual void OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField *pRspUserInvestor, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////交易编码查询应答
	//virtual void OnRspQryTradingCode(CUstpFtdcRspTradingCodeField *pRspTradingCode, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////投资者资金账户查询应答
	//virtual void OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField *pRspInvestorAccount, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////合约查询应答
	//virtual void OnRspQryInstrument(CUstpFtdcRspInstrumentField *pRspInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////交易所查询应答
	//virtual void OnRspQryExchange(CUstpFtdcRspExchangeField *pRspExchange, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////投资者持仓查询应答
	//virtual void OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField *pRspInvestorPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////订阅主题应答
	//virtual void OnRspSubscribeTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////合规参数查询应答
	//virtual void OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField *pRspComplianceParam, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	//
	/////主题查询应答
	//virtual void OnRspQryTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者手续费率查询应答
	//virtual void OnRspQryInvestorFee(CUstpFtdcInvestorFeeField *pInvestorFee, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者保证金率查询应答
	//virtual void OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField *pInvestorMargin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
virtual void OnFrontConnected(){
	AddMsg(new CThostSpiMessage(SPI::OnFrontConnected, (int *)NULL));
};


///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
virtual void OnFrontDisconnected(int nReason){
AddMsg(new CThostSpiMessage(SPI::OnFrontDisconnected, &nReason));
};



///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
virtual void OnHeartBeatWarning(int nTimeLapse){};

///客户端认证响应
virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspAuthenticate, pRspAuthenticateField, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///登录请求响应
virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspUserLogin, pRspUserLogin, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///登出请求响应
virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspUserLogout, pUserLogout, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///用户口令更新请求响应
virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspUserPasswordUpdate, pUserPasswordUpdate, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///资金账户口令更新请求响应
virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspTradingAccountPasswordUpdate, pTradingAccountPasswordUpdate, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///报单录入请求响应
virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspOrderInsert, pInputOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///预埋单录入请求响应
virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspParkedOrderInsert, pParkedOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///预埋撤单录入请求响应
virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspParkedOrderAction, pParkedOrderAction, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///报单操作请求响应
virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspOrderAction, pInputOrderAction, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///查询最大报单数量响应
virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQueryMaxOrderVolume, pQueryMaxOrderVolume, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///投资者结算结果确认响应
virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspSettlementInfoConfirm, pSettlementInfoConfirm, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///删除预埋单响应
virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspRemoveParkedOrder, pRemoveParkedOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///删除预埋撤单响应
virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspRemoveParkedOrderAction, pRemoveParkedOrderAction, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///执行宣告录入请求响应
virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspExecOrderInsert, pInputExecOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///执行宣告操作请求响应
virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspExecOrderAction, pInputExecOrderAction, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///询价录入请求响应
virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspForQuoteInsert, pInputForQuote, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///报价录入请求响应
virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQuoteInsert, pInputQuote, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///报价操作请求响应
virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQuoteAction, pInputQuoteAction, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询报单响应
virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryOrder, pOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询成交响应
virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryTrade, pTrade, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询投资者持仓响应
virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInvestorPosition, pInvestorPosition, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询资金账户响应
virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryTradingAccount, pTradingAccount, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询投资者响应
virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInvestor, pInvestor, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询交易编码响应
virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryTradingCode, pTradingCode, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询合约保证金率响应
virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInstrumentMarginRate, pInstrumentMarginRate, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询合约手续费率响应
virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInstrumentCommissionRate, pInstrumentCommissionRate, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询交易所响应
virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryExchange, pExchange, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询产品响应
virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryProduct, pProduct, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询合约响应
virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInstrument, pInstrument, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询行情响应
virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryDepthMarketData, pDepthMarketData, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询投资者结算结果响应
virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQrySettlementInfo, pSettlementInfo, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询转帐银行响应
virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryTransferBank, pTransferBank, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询投资者持仓明细响应
virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInvestorPositionDetail, pInvestorPositionDetail, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询客户通知响应
virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryNotice, pNotice, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询结算信息确认响应
virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQrySettlementInfoConfirm, pSettlementInfoConfirm, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询投资者持仓明细响应
virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInvestorPositionCombineDetail, pInvestorPositionCombineDetail, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///查询保证金监管系统经纪公司资金账户密钥响应
virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryCFMMCTradingAccountKey, pCFMMCTradingAccountKey, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询仓单折抵信息响应
virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryEWarrantOffset, pEWarrantOffset, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询投资者品种/跨品种保证金响应
virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryInvestorProductGroupMargin, pInvestorProductGroupMargin, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询交易所保证金率响应
virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryExchangeMarginRate, pExchangeMarginRate, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询交易所调整保证金率响应
virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryExchangeMarginRateAdjust, pExchangeMarginRateAdjust, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询汇率响应
virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryExchangeRate, pExchangeRate, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询二级代理操作员银期权限响应
virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQrySecAgentACIDMap, pSecAgentACIDMap, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询期权交易成本响应
virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryOptionInstrTradeCost, pOptionInstrTradeCost, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询期权合约手续费响应
virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryOptionInstrCommRate, pOptionInstrCommRate, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询执行宣告响应
virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryExecOrder, pExecOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询询价响应
virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryForQuote, pForQuote, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询报价响应
virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryQuote, pQuote, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询转帐流水响应
virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryTransferSerial, pTransferSerial, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询银期签约关系响应
virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryAccountregister, pAccountregister, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///错误应答
virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspError, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///报单通知
virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnOrder, pOrder));
};

///成交通知
virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnTrade, pTrade));
};

///报单录入错误回报
virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnOrderInsert, pInputOrder, (ThostFtdcRspInfoField*)pRspInfo));
};

///报单操作错误回报
virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnOrderAction, pOrderAction, (ThostFtdcRspInfoField*)pRspInfo));
};

///合约交易状态通知
virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnInstrumentStatus, pInstrumentStatus));
};

///交易通知
virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnTradingNotice, pTradingNoticeInfo));
};

///提示条件单校验错误
virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnErrorConditionalOrder, pErrorConditionalOrder));
};

///执行宣告通知
virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnExecOrder, pExecOrder));
};

///执行宣告录入错误回报
virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnExecOrderInsert, pInputExecOrder, (ThostFtdcRspInfoField*)pRspInfo));
};

///执行宣告操作错误回报
virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnExecOrderAction, pExecOrderAction, (ThostFtdcRspInfoField*)pRspInfo));
};

///询价录入错误回报
virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnForQuoteInsert, pInputForQuote, (ThostFtdcRspInfoField*)pRspInfo));
};

///报价通知
virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnQuote, pQuote));
};

///报价录入错误回报
virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnQuoteInsert, pInputQuote, (ThostFtdcRspInfoField*)pRspInfo));
};

///报价操作错误回报
virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnQuoteAction, pQuoteAction, (ThostFtdcRspInfoField*)pRspInfo));
};

///询价通知
virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnForQuoteRsp, pForQuoteRsp));
};

///请求查询签约银行响应
virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryContractBank, pContractBank, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询预埋单响应
virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryParkedOrder, pParkedOrder, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询预埋撤单响应
virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryParkedOrderAction, pParkedOrderAction, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询交易通知响应
virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryTradingNotice, pTradingNotice, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询经纪公司交易参数响应
virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryBrokerTradingParams, pBrokerTradingParams, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///请求查询经纪公司交易算法响应
virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQryBrokerTradingAlgos, pBrokerTradingAlgos, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///银行发起银行资金转期货通知
virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnFromBankToFutureByBank, pRspTransfer));
};

///银行发起期货资金转银行通知
virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnFromFutureToBankByBank, pRspTransfer));
};

///银行发起冲正银行转期货通知
virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnRepealFromBankToFutureByBank, pRspRepeal));
};

///银行发起冲正期货转银行通知
virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnRepealFromFutureToBankByBank, pRspRepeal));
};

///期货发起银行资金转期货通知
virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnFromBankToFutureByFuture, pRspTransfer));
};

///期货发起期货资金转银行通知
virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnFromFutureToBankByFuture, pRspTransfer));
};

///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnRepealFromBankToFutureByFutureManual, pRspRepeal));
};

///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnRepealFromFutureToBankByFutureManual, pRspRepeal));
};

///期货发起查询银行余额通知
virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnQueryBankBalanceByFuture, pNotifyQueryAccount));
};

///期货发起银行资金转期货错误回报
virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnBankToFutureByFuture, pReqTransfer, (ThostFtdcRspInfoField*)pRspInfo));
};

///期货发起期货资金转银行错误回报
virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnFutureToBankByFuture, pReqTransfer, (ThostFtdcRspInfoField*)pRspInfo));
};

///系统运行时期货端手工发起冲正银行转期货错误回报
virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnRepealBankToFutureByFutureManual, pReqRepeal, (ThostFtdcRspInfoField*)pRspInfo));
};

///系统运行时期货端手工发起冲正期货转银行错误回报
virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnRepealFutureToBankByFutureManual, pReqRepeal, (ThostFtdcRspInfoField*)pRspInfo));
};

///期货发起查询银行余额错误回报
virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) {
	AddMsg(new CThostSpiMessage(SPI::OnErrRtnQueryBankBalanceByFuture, pReqQueryAccount, (ThostFtdcRspInfoField*)pRspInfo));
};

///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnRepealFromBankToFutureByFuture, pRspRepeal));
};

///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnRepealFromFutureToBankByFuture, pRspRepeal));
};

///期货发起银行资金转期货应答
virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspFromBankToFutureByFuture, pReqTransfer, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///期货发起期货资金转银行应答
virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspFromFutureToBankByFuture, pReqTransfer, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///期货发起查询银行余额应答
virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	AddMsg(new CThostSpiMessage(SPI::OnRspQueryBankAccountMoneyByFuture, pReqQueryAccount, (ThostFtdcRspInfoField*)pRspInfo, nRequestID, bIsLast));
};

///银行发起银期开户通知
virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnOpenAccountByBank, pOpenAccount));
};

///银行发起银期销户通知
virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnCancelAccountByBank, pCancelAccount));
};

///银行发起变更银行账号通知
virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {
	AddMsg(new CThostSpiMessage(SPI::OnRtnChangeAccountByBank, pChangeAccount));
};

};
