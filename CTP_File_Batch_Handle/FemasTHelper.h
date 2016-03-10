#pragma once
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <atlwin.h>
#include "ThostFtdcUserApiStruct.h"
#include <winbase.h>
#include "FemasSpiMessage.h"
#include <ThostFtdcTraderApi.h>

class CMainDlg;
class CThostSpiMessage;
class CFemasTraderSpiHandler;

struct Func
{
	std::string param1;
	std::string parma2;
	std::string fname;
	std::function<int(int)> func;
};

struct Field
{
	std::string str;
	std::string name;
	std::string type;
	std::string fname;
	std::string val;
	void *ptr;
	CWindow* h_wnd;
	CWindow* label_wnd;
};

struct Type
{
	std::string name;
	std::string ftype;
	std::vector<std::vector<std::string> > lstrs;
	int len;
};

class CFemasTHelper
{
public:
	CFemasTHelper(CMainDlg* maindlg);
	int GenerateReqID();
	std::string GetRelativePath(const std::string &filepath = "");

	void AddSpiMsg(void* Handler, CThostSpiMessage * SpiMsg);
	void OnThostSpiMsg(CThostSpiMessage *pSpiMsg);
	void OnSpiDialogMsg(CThostSpiMessage *pSpiMsg);
	void Init();
	bool ShowFields( int fid, bool bShow = true );
	void SetTitle();
	Func												m_CurFunc;
	std::map<int, Func >								m_FemasReqFuncs;
	std::map<std::string, std::vector<Field> >			m_Fields;
	std::map<std::string, Type>							m_Types;
private:
	volatile LONG										m_SpiMsgQueueSize;
	std::map <int, CThostSpiMessagePack>				m_ThostSpiMessageCache;
	ThostFtdcRspInfoField*								m_pThostFtdcRspInfoField;
	CMainDlg*											m_pMainDlg;
	void												PrintHead( LPCTSTR Name, LPCTSTR Func, int Reqid, bool bLast );
	void												PrintHead( LPCTSTR Name, LPCTSTR Func );
	void												PrintDisconnectedReason( int nReason );
	void												AppendText( LPCTSTR text );
	int													DumpCThostFtdcField( std::string FieldName );
	void												PrintCThostFtdcRspInfoField( ThostFtdcRspInfoField *pRspInfo );
	std::string											GetNameByValue( std::vector <std::vector<std::string> > &vec, char val );
	//init
	void												InitMembers();
	void												InitTypes();
	void												InitFields();
	void												InitTraderApi();
	void												InitFunctions();
	void												RegType( std::string name, std::string ftype, std::string lstr = "", int len = 0 );
	void												RegField( std::string str, std::string name, std::string type, std::string fname, void *ptr, std::string val ="" );
	void												RegFun( int id, std::string name, std::function<int(int)>& func, std::string field, std::string filed2 = "");
	//field
	int													m_RequestID;




	CThostFtdcTraderApi*								m_pTraderApi;
	CFemasTraderSpiHandler*							m_pThostSpiHandler;
	//api 
	void												OnFrontConnected(CThostSpiMessage *pSpiMsg );
	void												OnFrontDisconnected( CThostSpiMessage *pSpiMsg);
    CThostFtdcDisseminationField                        m_ThostFtdcDisseminationField;
    CThostFtdcReqUserLoginField                         m_ThostFtdcReqUserLoginField;
    CThostFtdcRspUserLoginField                         m_ThostFtdcRspUserLoginField;
    CThostFtdcUserLogoutField                           m_ThostFtdcUserLogoutField;
    CThostFtdcForceUserLogoutField                      m_ThostFtdcForceUserLogoutField;
    CThostFtdcReqAuthenticateField                      m_ThostFtdcReqAuthenticateField;
    CThostFtdcRspAuthenticateField                      m_ThostFtdcRspAuthenticateField;
    CThostFtdcAuthenticationInfoField                   m_ThostFtdcAuthenticationInfoField;
    CThostFtdcTransferHeaderField                       m_ThostFtdcTransferHeaderField;
    CThostFtdcTransferBankToFutureReqField              m_ThostFtdcTransferBankToFutureReqField;
    CThostFtdcTransferBankToFutureRspField              m_ThostFtdcTransferBankToFutureRspField;
    CThostFtdcTransferFutureToBankReqField              m_ThostFtdcTransferFutureToBankReqField;
    CThostFtdcTransferFutureToBankRspField              m_ThostFtdcTransferFutureToBankRspField;
    CThostFtdcTransferQryBankReqField                   m_ThostFtdcTransferQryBankReqField;
    CThostFtdcTransferQryBankRspField                   m_ThostFtdcTransferQryBankRspField;
    CThostFtdcTransferQryDetailReqField                 m_ThostFtdcTransferQryDetailReqField;
    CThostFtdcTransferQryDetailRspField                 m_ThostFtdcTransferQryDetailRspField;
    CThostFtdcRspInfoField                              m_ThostFtdcRspInfoField;
    CThostFtdcExchangeField                             m_ThostFtdcExchangeField;
    CThostFtdcProductField                              m_ThostFtdcProductField;
    CThostFtdcInstrumentField                           m_ThostFtdcInstrumentField;
    CThostFtdcBrokerField                               m_ThostFtdcBrokerField;
    CThostFtdcTraderField                               m_ThostFtdcTraderField;
    CThostFtdcInvestorField                             m_ThostFtdcInvestorField;
    CThostFtdcTradingCodeField                          m_ThostFtdcTradingCodeField;
    CThostFtdcPartBrokerField                           m_ThostFtdcPartBrokerField;
    CThostFtdcSuperUserField                            m_ThostFtdcSuperUserField;
    CThostFtdcSuperUserFunctionField                    m_ThostFtdcSuperUserFunctionField;
    CThostFtdcInvestorGroupField                        m_ThostFtdcInvestorGroupField;
    CThostFtdcTradingAccountField                       m_ThostFtdcTradingAccountField;
    CThostFtdcInvestorPositionField                     m_ThostFtdcInvestorPositionField;
    CThostFtdcInstrumentMarginRateField                 m_ThostFtdcInstrumentMarginRateField;
    CThostFtdcInstrumentCommissionRateField             m_ThostFtdcInstrumentCommissionRateField;
    CThostFtdcDepthMarketDataField                      m_ThostFtdcDepthMarketDataField;
    CThostFtdcInstrumentTradingRightField               m_ThostFtdcInstrumentTradingRightField;
    CThostFtdcBrokerUserField                           m_ThostFtdcBrokerUserField;
    CThostFtdcBrokerUserPasswordField                   m_ThostFtdcBrokerUserPasswordField;
    CThostFtdcBrokerUserFunctionField                   m_ThostFtdcBrokerUserFunctionField;
    CThostFtdcTraderOfferField                          m_ThostFtdcTraderOfferField;
    CThostFtdcSettlementInfoField                       m_ThostFtdcSettlementInfoField;
    CThostFtdcInstrumentMarginRateAdjustField           m_ThostFtdcInstrumentMarginRateAdjustField;
    CThostFtdcExchangeMarginRateField                   m_ThostFtdcExchangeMarginRateField;
    CThostFtdcExchangeMarginRateAdjustField             m_ThostFtdcExchangeMarginRateAdjustField;
    CThostFtdcExchangeRateField                         m_ThostFtdcExchangeRateField;
    CThostFtdcSettlementRefField                        m_ThostFtdcSettlementRefField;
    CThostFtdcCurrentTimeField                          m_ThostFtdcCurrentTimeField;
    CThostFtdcCommPhaseField                            m_ThostFtdcCommPhaseField;
    CThostFtdcLoginInfoField                            m_ThostFtdcLoginInfoField;
    CThostFtdcLogoutAllField                            m_ThostFtdcLogoutAllField;
    CThostFtdcFrontStatusField                          m_ThostFtdcFrontStatusField;
    CThostFtdcUserPasswordUpdateField                   m_ThostFtdcUserPasswordUpdateField;
    CThostFtdcInputOrderField                           m_ThostFtdcInputOrderField;
    CThostFtdcOrderField                                m_ThostFtdcOrderField;
    CThostFtdcExchangeOrderField                        m_ThostFtdcExchangeOrderField;
    CThostFtdcExchangeOrderInsertErrorField             m_ThostFtdcExchangeOrderInsertErrorField;
    CThostFtdcInputOrderActionField                     m_ThostFtdcInputOrderActionField;
    CThostFtdcOrderActionField                          m_ThostFtdcOrderActionField;
    CThostFtdcExchangeOrderActionField                  m_ThostFtdcExchangeOrderActionField;
    CThostFtdcExchangeOrderActionErrorField             m_ThostFtdcExchangeOrderActionErrorField;
    CThostFtdcExchangeTradeField                        m_ThostFtdcExchangeTradeField;
    CThostFtdcTradeField                                m_ThostFtdcTradeField;
    CThostFtdcUserSessionField                          m_ThostFtdcUserSessionField;
    CThostFtdcQueryMaxOrderVolumeField                  m_ThostFtdcQueryMaxOrderVolumeField;
    CThostFtdcSettlementInfoConfirmField                m_ThostFtdcSettlementInfoConfirmField;
    CThostFtdcSyncDepositField                          m_ThostFtdcSyncDepositField;
    CThostFtdcSyncFundMortgageField                     m_ThostFtdcSyncFundMortgageField;
    CThostFtdcBrokerSyncField                           m_ThostFtdcBrokerSyncField;
    CThostFtdcSyncingInvestorField                      m_ThostFtdcSyncingInvestorField;
    CThostFtdcSyncingTradingCodeField                   m_ThostFtdcSyncingTradingCodeField;
    CThostFtdcSyncingInvestorGroupField                 m_ThostFtdcSyncingInvestorGroupField;
    CThostFtdcSyncingTradingAccountField                m_ThostFtdcSyncingTradingAccountField;
    CThostFtdcSyncingInvestorPositionField              m_ThostFtdcSyncingInvestorPositionField;
    CThostFtdcSyncingInstrumentMarginRateField          m_ThostFtdcSyncingInstrumentMarginRateField;
    CThostFtdcSyncingInstrumentCommissionRateField      m_ThostFtdcSyncingInstrumentCommissionRateField;
    CThostFtdcSyncingInstrumentTradingRightField        m_ThostFtdcSyncingInstrumentTradingRightField;
    CThostFtdcQryOrderField                             m_ThostFtdcQryOrderField;
    CThostFtdcQryTradeField                             m_ThostFtdcQryTradeField;
    CThostFtdcQryInvestorPositionField                  m_ThostFtdcQryInvestorPositionField;
    CThostFtdcQryTradingAccountField                    m_ThostFtdcQryTradingAccountField;
    CThostFtdcQryInvestorField                          m_ThostFtdcQryInvestorField;
    CThostFtdcQryTradingCodeField                       m_ThostFtdcQryTradingCodeField;
    CThostFtdcQryInvestorGroupField                     m_ThostFtdcQryInvestorGroupField;
    CThostFtdcQryInstrumentMarginRateField              m_ThostFtdcQryInstrumentMarginRateField;
    CThostFtdcQryInstrumentCommissionRateField          m_ThostFtdcQryInstrumentCommissionRateField;
    CThostFtdcQryInstrumentTradingRightField            m_ThostFtdcQryInstrumentTradingRightField;
    CThostFtdcQryBrokerField                            m_ThostFtdcQryBrokerField;
    CThostFtdcQryTraderField                            m_ThostFtdcQryTraderField;
    CThostFtdcQrySuperUserFunctionField                 m_ThostFtdcQrySuperUserFunctionField;
    CThostFtdcQryUserSessionField                       m_ThostFtdcQryUserSessionField;
    CThostFtdcQryPartBrokerField                        m_ThostFtdcQryPartBrokerField;
    CThostFtdcQryFrontStatusField                       m_ThostFtdcQryFrontStatusField;
    CThostFtdcQryExchangeOrderField                     m_ThostFtdcQryExchangeOrderField;
    CThostFtdcQryOrderActionField                       m_ThostFtdcQryOrderActionField;
    CThostFtdcQryExchangeOrderActionField               m_ThostFtdcQryExchangeOrderActionField;
    CThostFtdcQrySuperUserField                         m_ThostFtdcQrySuperUserField;
    CThostFtdcQryExchangeField                          m_ThostFtdcQryExchangeField;
    CThostFtdcQryProductField                           m_ThostFtdcQryProductField;
    CThostFtdcQryInstrumentField                        m_ThostFtdcQryInstrumentField;
    CThostFtdcQryDepthMarketDataField                   m_ThostFtdcQryDepthMarketDataField;
    CThostFtdcQryBrokerUserField                        m_ThostFtdcQryBrokerUserField;
    CThostFtdcQryBrokerUserFunctionField                m_ThostFtdcQryBrokerUserFunctionField;
    CThostFtdcQryTraderOfferField                       m_ThostFtdcQryTraderOfferField;
    CThostFtdcQrySyncDepositField                       m_ThostFtdcQrySyncDepositField;
    CThostFtdcQrySettlementInfoField                    m_ThostFtdcQrySettlementInfoField;
    CThostFtdcQryExchangeMarginRateField                m_ThostFtdcQryExchangeMarginRateField;
    CThostFtdcQryExchangeMarginRateAdjustField          m_ThostFtdcQryExchangeMarginRateAdjustField;
    CThostFtdcQryExchangeRateField                      m_ThostFtdcQryExchangeRateField;
    CThostFtdcQrySyncFundMortgageField                  m_ThostFtdcQrySyncFundMortgageField;
    CThostFtdcQryHisOrderField                          m_ThostFtdcQryHisOrderField;
    CThostFtdcOptionInstrMiniMarginField                m_ThostFtdcOptionInstrMiniMarginField;
    CThostFtdcOptionInstrMarginAdjustField              m_ThostFtdcOptionInstrMarginAdjustField;
    CThostFtdcOptionInstrCommRateField                  m_ThostFtdcOptionInstrCommRateField;
    CThostFtdcOptionInstrTradeCostField                 m_ThostFtdcOptionInstrTradeCostField;
    CThostFtdcQryOptionInstrTradeCostField              m_ThostFtdcQryOptionInstrTradeCostField;
    CThostFtdcQryOptionInstrCommRateField               m_ThostFtdcQryOptionInstrCommRateField;
    CThostFtdcIndexPriceField                           m_ThostFtdcIndexPriceField;
    CThostFtdcInputExecOrderField                       m_ThostFtdcInputExecOrderField;
    CThostFtdcInputExecOrderActionField                 m_ThostFtdcInputExecOrderActionField;
    CThostFtdcExecOrderField                            m_ThostFtdcExecOrderField;
    CThostFtdcExecOrderActionField                      m_ThostFtdcExecOrderActionField;
    CThostFtdcQryExecOrderField                         m_ThostFtdcQryExecOrderField;
    CThostFtdcExchangeExecOrderField                    m_ThostFtdcExchangeExecOrderField;
    CThostFtdcQryExchangeExecOrderField                 m_ThostFtdcQryExchangeExecOrderField;
    CThostFtdcQryExecOrderActionField                   m_ThostFtdcQryExecOrderActionField;
    CThostFtdcExchangeExecOrderActionField              m_ThostFtdcExchangeExecOrderActionField;
    CThostFtdcQryExchangeExecOrderActionField           m_ThostFtdcQryExchangeExecOrderActionField;
    CThostFtdcErrExecOrderField                         m_ThostFtdcErrExecOrderField;
    CThostFtdcQryErrExecOrderField                      m_ThostFtdcQryErrExecOrderField;
    CThostFtdcErrExecOrderActionField                   m_ThostFtdcErrExecOrderActionField;
    CThostFtdcQryErrExecOrderActionField                m_ThostFtdcQryErrExecOrderActionField;
    CThostFtdcOptionInstrTradingRightField              m_ThostFtdcOptionInstrTradingRightField;
    CThostFtdcQryOptionInstrTradingRightField           m_ThostFtdcQryOptionInstrTradingRightField;
    CThostFtdcInputForQuoteField                        m_ThostFtdcInputForQuoteField;
    CThostFtdcForQuoteField                             m_ThostFtdcForQuoteField;
    CThostFtdcQryForQuoteField                          m_ThostFtdcQryForQuoteField;
    CThostFtdcExchangeForQuoteField                     m_ThostFtdcExchangeForQuoteField;
    CThostFtdcQryExchangeForQuoteField                  m_ThostFtdcQryExchangeForQuoteField;
    CThostFtdcInputQuoteField                           m_ThostFtdcInputQuoteField;
    CThostFtdcInputQuoteActionField                     m_ThostFtdcInputQuoteActionField;
    CThostFtdcQuoteField                                m_ThostFtdcQuoteField;
    CThostFtdcQuoteActionField                          m_ThostFtdcQuoteActionField;
    CThostFtdcQryQuoteField                             m_ThostFtdcQryQuoteField;
    CThostFtdcExchangeQuoteField                        m_ThostFtdcExchangeQuoteField;
    CThostFtdcQryExchangeQuoteField                     m_ThostFtdcQryExchangeQuoteField;
    CThostFtdcQryQuoteActionField                       m_ThostFtdcQryQuoteActionField;
    CThostFtdcExchangeQuoteActionField                  m_ThostFtdcExchangeQuoteActionField;
    CThostFtdcQryExchangeQuoteActionField               m_ThostFtdcQryExchangeQuoteActionField;
    CThostFtdcOptionInstrDeltaField                     m_ThostFtdcOptionInstrDeltaField;
    CThostFtdcForQuoteRspField                          m_ThostFtdcForQuoteRspField;
    CThostFtdcStrikeOffsetField                         m_ThostFtdcStrikeOffsetField;
    CThostFtdcQryStrikeOffsetField                      m_ThostFtdcQryStrikeOffsetField;
    CThostFtdcMarketDataField                           m_ThostFtdcMarketDataField;
    CThostFtdcMarketDataBaseField                       m_ThostFtdcMarketDataBaseField;
    CThostFtdcMarketDataStaticField                     m_ThostFtdcMarketDataStaticField;
    CThostFtdcMarketDataLastMatchField                  m_ThostFtdcMarketDataLastMatchField;
    CThostFtdcMarketDataBestPriceField                  m_ThostFtdcMarketDataBestPriceField;
    CThostFtdcMarketDataBid23Field                      m_ThostFtdcMarketDataBid23Field;
    CThostFtdcMarketDataAsk23Field                      m_ThostFtdcMarketDataAsk23Field;
    CThostFtdcMarketDataBid45Field                      m_ThostFtdcMarketDataBid45Field;
    CThostFtdcMarketDataAsk45Field                      m_ThostFtdcMarketDataAsk45Field;
    CThostFtdcMarketDataUpdateTimeField                 m_ThostFtdcMarketDataUpdateTimeField;
    CThostFtdcMarketDataExchangeField                   m_ThostFtdcMarketDataExchangeField;
    CThostFtdcSpecificInstrumentField                   m_ThostFtdcSpecificInstrumentField;
    CThostFtdcInstrumentStatusField                     m_ThostFtdcInstrumentStatusField;
    CThostFtdcQryInstrumentStatusField                  m_ThostFtdcQryInstrumentStatusField;
    CThostFtdcInvestorAccountField                      m_ThostFtdcInvestorAccountField;
    CThostFtdcPositionProfitAlgorithmField              m_ThostFtdcPositionProfitAlgorithmField;
    CThostFtdcDiscountField                             m_ThostFtdcDiscountField;
    CThostFtdcQryTransferBankField                      m_ThostFtdcQryTransferBankField;
    CThostFtdcTransferBankField                         m_ThostFtdcTransferBankField;
    CThostFtdcQryInvestorPositionDetailField            m_ThostFtdcQryInvestorPositionDetailField;
    CThostFtdcInvestorPositionDetailField               m_ThostFtdcInvestorPositionDetailField;
    CThostFtdcTradingAccountPasswordField               m_ThostFtdcTradingAccountPasswordField;
    CThostFtdcMDTraderOfferField                        m_ThostFtdcMDTraderOfferField;
    CThostFtdcQryMDTraderOfferField                     m_ThostFtdcQryMDTraderOfferField;
    CThostFtdcQryNoticeField                            m_ThostFtdcQryNoticeField;
    CThostFtdcNoticeField                               m_ThostFtdcNoticeField;
    CThostFtdcUserRightField                            m_ThostFtdcUserRightField;
    CThostFtdcQrySettlementInfoConfirmField             m_ThostFtdcQrySettlementInfoConfirmField;
    CThostFtdcLoadSettlementInfoField                   m_ThostFtdcLoadSettlementInfoField;
    CThostFtdcBrokerWithdrawAlgorithmField              m_ThostFtdcBrokerWithdrawAlgorithmField;
    CThostFtdcTradingAccountPasswordUpdateV1Field       m_ThostFtdcTradingAccountPasswordUpdateV1Field;
    CThostFtdcTradingAccountPasswordUpdateField         m_ThostFtdcTradingAccountPasswordUpdateField;
    CThostFtdcQryCombinationLegField                    m_ThostFtdcQryCombinationLegField;
    CThostFtdcQrySyncStatusField                        m_ThostFtdcQrySyncStatusField;
    CThostFtdcCombinationLegField                       m_ThostFtdcCombinationLegField;
    CThostFtdcSyncStatusField                           m_ThostFtdcSyncStatusField;
    CThostFtdcQryLinkManField                           m_ThostFtdcQryLinkManField;
    CThostFtdcLinkManField                              m_ThostFtdcLinkManField;
    CThostFtdcQryBrokerUserEventField                   m_ThostFtdcQryBrokerUserEventField;
    CThostFtdcBrokerUserEventField                      m_ThostFtdcBrokerUserEventField;
    CThostFtdcQryContractBankField                      m_ThostFtdcQryContractBankField;
    CThostFtdcContractBankField                         m_ThostFtdcContractBankField;
    CThostFtdcInvestorPositionCombineDetailField        m_ThostFtdcInvestorPositionCombineDetailField;
    CThostFtdcParkedOrderField                          m_ThostFtdcParkedOrderField;
    CThostFtdcParkedOrderActionField                    m_ThostFtdcParkedOrderActionField;
    CThostFtdcQryParkedOrderField                       m_ThostFtdcQryParkedOrderField;
    CThostFtdcQryParkedOrderActionField                 m_ThostFtdcQryParkedOrderActionField;
    CThostFtdcRemoveParkedOrderField                    m_ThostFtdcRemoveParkedOrderField;
    CThostFtdcRemoveParkedOrderActionField              m_ThostFtdcRemoveParkedOrderActionField;
    CThostFtdcInvestorWithdrawAlgorithmField            m_ThostFtdcInvestorWithdrawAlgorithmField;
    CThostFtdcQryInvestorPositionCombineDetailField     m_ThostFtdcQryInvestorPositionCombineDetailField;
    CThostFtdcMarketDataAveragePriceField               m_ThostFtdcMarketDataAveragePriceField;
    CThostFtdcVerifyInvestorPasswordField               m_ThostFtdcVerifyInvestorPasswordField;
    CThostFtdcUserIPField                               m_ThostFtdcUserIPField;
    CThostFtdcTradingNoticeInfoField                    m_ThostFtdcTradingNoticeInfoField;
    CThostFtdcTradingNoticeField                        m_ThostFtdcTradingNoticeField;
    CThostFtdcQryTradingNoticeField                     m_ThostFtdcQryTradingNoticeField;
    CThostFtdcQryErrOrderField                          m_ThostFtdcQryErrOrderField;
    CThostFtdcErrOrderField                             m_ThostFtdcErrOrderField;
    CThostFtdcErrorConditionalOrderField                m_ThostFtdcErrorConditionalOrderField;
    CThostFtdcQryErrOrderActionField                    m_ThostFtdcQryErrOrderActionField;
    CThostFtdcErrOrderActionField                       m_ThostFtdcErrOrderActionField;
    CThostFtdcQryExchangeSequenceField                  m_ThostFtdcQryExchangeSequenceField;
    CThostFtdcExchangeSequenceField                     m_ThostFtdcExchangeSequenceField;
    CThostFtdcQueryMaxOrderVolumeWithPriceField         m_ThostFtdcQueryMaxOrderVolumeWithPriceField;
    CThostFtdcQryBrokerTradingParamsField               m_ThostFtdcQryBrokerTradingParamsField;
    CThostFtdcBrokerTradingParamsField                  m_ThostFtdcBrokerTradingParamsField;
    CThostFtdcQryBrokerTradingAlgosField                m_ThostFtdcQryBrokerTradingAlgosField;
    CThostFtdcBrokerTradingAlgosField                   m_ThostFtdcBrokerTradingAlgosField;
    CThostFtdcQueryBrokerDepositField                   m_ThostFtdcQueryBrokerDepositField;
    CThostFtdcBrokerDepositField                        m_ThostFtdcBrokerDepositField;
    CThostFtdcQryCFMMCBrokerKeyField                    m_ThostFtdcQryCFMMCBrokerKeyField;
    CThostFtdcCFMMCBrokerKeyField                       m_ThostFtdcCFMMCBrokerKeyField;
    CThostFtdcCFMMCTradingAccountKeyField               m_ThostFtdcCFMMCTradingAccountKeyField;
    CThostFtdcQryCFMMCTradingAccountKeyField            m_ThostFtdcQryCFMMCTradingAccountKeyField;
    CThostFtdcBrokerUserOTPParamField                   m_ThostFtdcBrokerUserOTPParamField;
    CThostFtdcManualSyncBrokerUserOTPField              m_ThostFtdcManualSyncBrokerUserOTPField;
    CThostFtdcCommRateModelField                        m_ThostFtdcCommRateModelField;
    CThostFtdcQryCommRateModelField                     m_ThostFtdcQryCommRateModelField;
    CThostFtdcMarginModelField                          m_ThostFtdcMarginModelField;
    CThostFtdcQryMarginModelField                       m_ThostFtdcQryMarginModelField;
    CThostFtdcEWarrantOffsetField                       m_ThostFtdcEWarrantOffsetField;
    CThostFtdcQryEWarrantOffsetField                    m_ThostFtdcQryEWarrantOffsetField;
    CThostFtdcQryInvestorProductGroupMarginField        m_ThostFtdcQryInvestorProductGroupMarginField;
    CThostFtdcInvestorProductGroupMarginField           m_ThostFtdcInvestorProductGroupMarginField;
    CThostFtdcReqOpenAccountField                       m_ThostFtdcReqOpenAccountField;
    CThostFtdcReqCancelAccountField                     m_ThostFtdcReqCancelAccountField;
    CThostFtdcReqChangeAccountField                     m_ThostFtdcReqChangeAccountField;
    CThostFtdcReqTransferField                          m_ThostFtdcReqTransferField;
    CThostFtdcRspTransferField                          m_ThostFtdcRspTransferField;
    CThostFtdcReqRepealField                            m_ThostFtdcReqRepealField;
    CThostFtdcRspRepealField                            m_ThostFtdcRspRepealField;
    CThostFtdcReqQueryAccountField                      m_ThostFtdcReqQueryAccountField;
    CThostFtdcRspQueryAccountField                      m_ThostFtdcRspQueryAccountField;
    CThostFtdcFutureSignIOField                         m_ThostFtdcFutureSignIOField;
    CThostFtdcRspFutureSignInField                      m_ThostFtdcRspFutureSignInField;
    CThostFtdcReqFutureSignOutField                     m_ThostFtdcReqFutureSignOutField;
    CThostFtdcRspFutureSignOutField                     m_ThostFtdcRspFutureSignOutField;
    CThostFtdcReqQueryTradeResultBySerialField          m_ThostFtdcReqQueryTradeResultBySerialField;
    CThostFtdcRspQueryTradeResultBySerialField          m_ThostFtdcRspQueryTradeResultBySerialField;
    CThostFtdcReqDayEndFileReadyField                   m_ThostFtdcReqDayEndFileReadyField;
    CThostFtdcReturnResultField                         m_ThostFtdcReturnResultField;
    CThostFtdcVerifyFuturePasswordField                 m_ThostFtdcVerifyFuturePasswordField;
    CThostFtdcVerifyCustInfoField                       m_ThostFtdcVerifyCustInfoField;
    CThostFtdcVerifyFuturePasswordAndCustInfoField      m_ThostFtdcVerifyFuturePasswordAndCustInfoField;
    CThostFtdcDepositResultInformField                  m_ThostFtdcDepositResultInformField;
    CThostFtdcReqSyncKeyField                           m_ThostFtdcReqSyncKeyField;
    CThostFtdcRspSyncKeyField                           m_ThostFtdcRspSyncKeyField;
    CThostFtdcNotifyQueryAccountField                   m_ThostFtdcNotifyQueryAccountField;
    CThostFtdcTransferSerialField                       m_ThostFtdcTransferSerialField;
    CThostFtdcQryTransferSerialField                    m_ThostFtdcQryTransferSerialField;
    CThostFtdcNotifyFutureSignInField                   m_ThostFtdcNotifyFutureSignInField;
    CThostFtdcNotifyFutureSignOutField                  m_ThostFtdcNotifyFutureSignOutField;
    CThostFtdcNotifySyncKeyField                        m_ThostFtdcNotifySyncKeyField;
    CThostFtdcQryAccountregisterField                   m_ThostFtdcQryAccountregisterField;
    CThostFtdcAccountregisterField                      m_ThostFtdcAccountregisterField;
    CThostFtdcOpenAccountField                          m_ThostFtdcOpenAccountField;
    CThostFtdcCancelAccountField                        m_ThostFtdcCancelAccountField;
    CThostFtdcChangeAccountField                        m_ThostFtdcChangeAccountField;
    CThostFtdcSecAgentACIDMapField                      m_ThostFtdcSecAgentACIDMapField;
    CThostFtdcQrySecAgentACIDMapField                   m_ThostFtdcQrySecAgentACIDMapField;
    CThostFtdcUserRightsAssignField                     m_ThostFtdcUserRightsAssignField;
    CThostFtdcBrokerUserRightAssignField                m_ThostFtdcBrokerUserRightAssignField;
    CThostFtdcDRTransferField                           m_ThostFtdcDRTransferField;
    CThostFtdcFensUserInfoField                         m_ThostFtdcFensUserInfoField;
    CThostFtdcCurrTransferIdentityField                 m_ThostFtdcCurrTransferIdentityField;
    CThostFtdcLoginForbiddenUserField                   m_ThostFtdcLoginForbiddenUserField;
    CThostFtdcQryLoginForbiddenUserField                m_ThostFtdcQryLoginForbiddenUserField;
    CThostFtdcMulticastGroupInfoField                   m_ThostFtdcMulticastGroupInfoField;
    CThostFtdcTradingAccountReserveField                m_ThostFtdcTradingAccountReserveField;
    void                                                OnRspAuthenticate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspUserLogin(CThostSpiMessage *pSpiMsg);
    void                                                OnRspUserLogout(CThostSpiMessage *pSpiMsg);
    void                                                OnRspUserPasswordUpdate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspTradingAccountPasswordUpdate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspOrderInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnRspParkedOrderInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnRspParkedOrderAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRspOrderAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQueryMaxOrderVolume(CThostSpiMessage *pSpiMsg);
    void                                                OnRspSettlementInfoConfirm(CThostSpiMessage *pSpiMsg);
    void                                                OnRspRemoveParkedOrder(CThostSpiMessage *pSpiMsg);
    void                                                OnRspRemoveParkedOrderAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRspExecOrderInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnRspExecOrderAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRspForQuoteInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQuoteInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQuoteAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryOrder(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryTrade(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInvestorPosition(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryTradingAccount(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInvestor(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryTradingCode(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInstrumentMarginRate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInstrumentCommissionRate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryExchange(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryProduct(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInstrument(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryDepthMarketData(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQrySettlementInfo(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryTransferBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInvestorPositionDetail(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryNotice(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQrySettlementInfoConfirm(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInvestorPositionCombineDetail(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryCFMMCTradingAccountKey(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryEWarrantOffset(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryInvestorProductGroupMargin(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryExchangeMarginRate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryExchangeMarginRateAdjust(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryExchangeRate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQrySecAgentACIDMap(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryOptionInstrTradeCost(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryOptionInstrCommRate(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryExecOrder(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryForQuote(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryQuote(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryTransferSerial(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryAccountregister(CThostSpiMessage *pSpiMsg);
    void                                                OnRspError(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnOrder(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnTrade(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnOrderInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnOrderAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnInstrumentStatus(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnTradingNotice(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnErrorConditionalOrder(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnExecOrder(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnExecOrderInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnExecOrderAction(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnForQuoteInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnQuote(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnQuoteInsert(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnQuoteAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnForQuoteRsp(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryContractBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryParkedOrder(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryParkedOrderAction(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryTradingNotice(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryBrokerTradingParams(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQryBrokerTradingAlgos(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnFromBankToFutureByBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnFromFutureToBankByBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnRepealFromBankToFutureByBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnRepealFromFutureToBankByBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnFromBankToFutureByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnFromFutureToBankByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnRepealFromBankToFutureByFutureManual(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnRepealFromFutureToBankByFutureManual(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnQueryBankBalanceByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnBankToFutureByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnFutureToBankByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnRepealBankToFutureByFutureManual(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnRepealFutureToBankByFutureManual(CThostSpiMessage *pSpiMsg);
    void                                                OnErrRtnQueryBankBalanceByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnRepealFromBankToFutureByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnRepealFromFutureToBankByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRspFromBankToFutureByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRspFromFutureToBankByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRspQueryBankAccountMoneyByFuture(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnOpenAccountByBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnCancelAccountByBank(CThostSpiMessage *pSpiMsg);
    void                                                OnRtnChangeAccountByBank(CThostSpiMessage *pSpiMsg);
};