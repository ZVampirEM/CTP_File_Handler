#include "stdafx.h"
#include "FemasTHelper.h"
#include "atlmisc.h"
#include <winuser.h>
#include "atlctrls.h"
#include "MainDlg.h"
#include "ThostFtdcTraderApi.h"
#include "TraderFemasHandler.h"
#include <sstream>
#include <boost\algorithm\string\split.hpp>
#include <boost\algorithm\string\classification.hpp>

CFemasTHelper::CFemasTHelper( CMainDlg* maindlg ) 
	: m_RequestID(0)
	, m_pMainDlg(maindlg)
	, m_pTraderApi(NULL)
	, m_pThostSpiHandler(NULL)
	, m_SpiMsgQueueSize(0)
{
	m_pThostFtdcRspInfoField = new ThostFtdcRspInfoField;
}

void CFemasTHelper::InitMembers()
{
	ZeroMemory(&m_ThostFtdcDisseminationField, sizeof(m_ThostFtdcDisseminationField));
	ZeroMemory(&m_ThostFtdcReqUserLoginField, sizeof(m_ThostFtdcReqUserLoginField));
	ZeroMemory(&m_ThostFtdcRspUserLoginField, sizeof(m_ThostFtdcRspUserLoginField));
	ZeroMemory(&m_ThostFtdcUserLogoutField, sizeof(m_ThostFtdcUserLogoutField));
	ZeroMemory(&m_ThostFtdcForceUserLogoutField, sizeof(m_ThostFtdcForceUserLogoutField));
	ZeroMemory(&m_ThostFtdcReqAuthenticateField, sizeof(m_ThostFtdcReqAuthenticateField));
	ZeroMemory(&m_ThostFtdcRspAuthenticateField, sizeof(m_ThostFtdcRspAuthenticateField));
	ZeroMemory(&m_ThostFtdcAuthenticationInfoField, sizeof(m_ThostFtdcAuthenticationInfoField));
	ZeroMemory(&m_ThostFtdcTransferHeaderField, sizeof(m_ThostFtdcTransferHeaderField));
	ZeroMemory(&m_ThostFtdcTransferBankToFutureReqField, sizeof(m_ThostFtdcTransferBankToFutureReqField));
	ZeroMemory(&m_ThostFtdcTransferBankToFutureRspField, sizeof(m_ThostFtdcTransferBankToFutureRspField));
	ZeroMemory(&m_ThostFtdcTransferFutureToBankReqField, sizeof(m_ThostFtdcTransferFutureToBankReqField));
	ZeroMemory(&m_ThostFtdcTransferFutureToBankRspField, sizeof(m_ThostFtdcTransferFutureToBankRspField));
	ZeroMemory(&m_ThostFtdcTransferQryBankReqField, sizeof(m_ThostFtdcTransferQryBankReqField));
	ZeroMemory(&m_ThostFtdcTransferQryBankRspField, sizeof(m_ThostFtdcTransferQryBankRspField));
	ZeroMemory(&m_ThostFtdcTransferQryDetailReqField, sizeof(m_ThostFtdcTransferQryDetailReqField));
	ZeroMemory(&m_ThostFtdcTransferQryDetailRspField, sizeof(m_ThostFtdcTransferQryDetailRspField));
	ZeroMemory(&m_ThostFtdcRspInfoField, sizeof(m_ThostFtdcRspInfoField));
	ZeroMemory(&m_ThostFtdcExchangeField, sizeof(m_ThostFtdcExchangeField));
	ZeroMemory(&m_ThostFtdcProductField, sizeof(m_ThostFtdcProductField));
	ZeroMemory(&m_ThostFtdcInstrumentField, sizeof(m_ThostFtdcInstrumentField));
	ZeroMemory(&m_ThostFtdcBrokerField, sizeof(m_ThostFtdcBrokerField));
	ZeroMemory(&m_ThostFtdcTraderField, sizeof(m_ThostFtdcTraderField));
	ZeroMemory(&m_ThostFtdcInvestorField, sizeof(m_ThostFtdcInvestorField));
	ZeroMemory(&m_ThostFtdcTradingCodeField, sizeof(m_ThostFtdcTradingCodeField));
	ZeroMemory(&m_ThostFtdcPartBrokerField, sizeof(m_ThostFtdcPartBrokerField));
	ZeroMemory(&m_ThostFtdcSuperUserField, sizeof(m_ThostFtdcSuperUserField));
	ZeroMemory(&m_ThostFtdcSuperUserFunctionField, sizeof(m_ThostFtdcSuperUserFunctionField));
	ZeroMemory(&m_ThostFtdcInvestorGroupField, sizeof(m_ThostFtdcInvestorGroupField));
	ZeroMemory(&m_ThostFtdcTradingAccountField, sizeof(m_ThostFtdcTradingAccountField));
	ZeroMemory(&m_ThostFtdcInvestorPositionField, sizeof(m_ThostFtdcInvestorPositionField));
	ZeroMemory(&m_ThostFtdcInstrumentMarginRateField, sizeof(m_ThostFtdcInstrumentMarginRateField));
	ZeroMemory(&m_ThostFtdcInstrumentCommissionRateField, sizeof(m_ThostFtdcInstrumentCommissionRateField));
	ZeroMemory(&m_ThostFtdcDepthMarketDataField, sizeof(m_ThostFtdcDepthMarketDataField));
	ZeroMemory(&m_ThostFtdcInstrumentTradingRightField, sizeof(m_ThostFtdcInstrumentTradingRightField));
	ZeroMemory(&m_ThostFtdcBrokerUserField, sizeof(m_ThostFtdcBrokerUserField));
	ZeroMemory(&m_ThostFtdcBrokerUserPasswordField, sizeof(m_ThostFtdcBrokerUserPasswordField));
	ZeroMemory(&m_ThostFtdcBrokerUserFunctionField, sizeof(m_ThostFtdcBrokerUserFunctionField));
	ZeroMemory(&m_ThostFtdcTraderOfferField, sizeof(m_ThostFtdcTraderOfferField));
	ZeroMemory(&m_ThostFtdcSettlementInfoField, sizeof(m_ThostFtdcSettlementInfoField));
	ZeroMemory(&m_ThostFtdcInstrumentMarginRateAdjustField, sizeof(m_ThostFtdcInstrumentMarginRateAdjustField));
	ZeroMemory(&m_ThostFtdcExchangeMarginRateField, sizeof(m_ThostFtdcExchangeMarginRateField));
	ZeroMemory(&m_ThostFtdcExchangeMarginRateAdjustField, sizeof(m_ThostFtdcExchangeMarginRateAdjustField));
	ZeroMemory(&m_ThostFtdcExchangeRateField, sizeof(m_ThostFtdcExchangeRateField));
	ZeroMemory(&m_ThostFtdcSettlementRefField, sizeof(m_ThostFtdcSettlementRefField));
	ZeroMemory(&m_ThostFtdcCurrentTimeField, sizeof(m_ThostFtdcCurrentTimeField));
	ZeroMemory(&m_ThostFtdcCommPhaseField, sizeof(m_ThostFtdcCommPhaseField));
	ZeroMemory(&m_ThostFtdcLoginInfoField, sizeof(m_ThostFtdcLoginInfoField));
	ZeroMemory(&m_ThostFtdcLogoutAllField, sizeof(m_ThostFtdcLogoutAllField));
	ZeroMemory(&m_ThostFtdcFrontStatusField, sizeof(m_ThostFtdcFrontStatusField));
	ZeroMemory(&m_ThostFtdcUserPasswordUpdateField, sizeof(m_ThostFtdcUserPasswordUpdateField));
	ZeroMemory(&m_ThostFtdcInputOrderField, sizeof(m_ThostFtdcInputOrderField));
	ZeroMemory(&m_ThostFtdcOrderField, sizeof(m_ThostFtdcOrderField));
	ZeroMemory(&m_ThostFtdcExchangeOrderField, sizeof(m_ThostFtdcExchangeOrderField));
	ZeroMemory(&m_ThostFtdcExchangeOrderInsertErrorField, sizeof(m_ThostFtdcExchangeOrderInsertErrorField));
	ZeroMemory(&m_ThostFtdcInputOrderActionField, sizeof(m_ThostFtdcInputOrderActionField));
	ZeroMemory(&m_ThostFtdcOrderActionField, sizeof(m_ThostFtdcOrderActionField));
	ZeroMemory(&m_ThostFtdcExchangeOrderActionField, sizeof(m_ThostFtdcExchangeOrderActionField));
	ZeroMemory(&m_ThostFtdcExchangeOrderActionErrorField, sizeof(m_ThostFtdcExchangeOrderActionErrorField));
	ZeroMemory(&m_ThostFtdcExchangeTradeField, sizeof(m_ThostFtdcExchangeTradeField));
	ZeroMemory(&m_ThostFtdcTradeField, sizeof(m_ThostFtdcTradeField));
	ZeroMemory(&m_ThostFtdcUserSessionField, sizeof(m_ThostFtdcUserSessionField));
	ZeroMemory(&m_ThostFtdcQueryMaxOrderVolumeField, sizeof(m_ThostFtdcQueryMaxOrderVolumeField));
	ZeroMemory(&m_ThostFtdcSettlementInfoConfirmField, sizeof(m_ThostFtdcSettlementInfoConfirmField));
	ZeroMemory(&m_ThostFtdcSyncDepositField, sizeof(m_ThostFtdcSyncDepositField));
	ZeroMemory(&m_ThostFtdcSyncFundMortgageField, sizeof(m_ThostFtdcSyncFundMortgageField));
	ZeroMemory(&m_ThostFtdcBrokerSyncField, sizeof(m_ThostFtdcBrokerSyncField));
	ZeroMemory(&m_ThostFtdcSyncingInvestorField, sizeof(m_ThostFtdcSyncingInvestorField));
	ZeroMemory(&m_ThostFtdcSyncingTradingCodeField, sizeof(m_ThostFtdcSyncingTradingCodeField));
	ZeroMemory(&m_ThostFtdcSyncingInvestorGroupField, sizeof(m_ThostFtdcSyncingInvestorGroupField));
	ZeroMemory(&m_ThostFtdcSyncingTradingAccountField, sizeof(m_ThostFtdcSyncingTradingAccountField));
	ZeroMemory(&m_ThostFtdcSyncingInvestorPositionField, sizeof(m_ThostFtdcSyncingInvestorPositionField));
	ZeroMemory(&m_ThostFtdcSyncingInstrumentMarginRateField, sizeof(m_ThostFtdcSyncingInstrumentMarginRateField));
	ZeroMemory(&m_ThostFtdcSyncingInstrumentCommissionRateField, sizeof(m_ThostFtdcSyncingInstrumentCommissionRateField));
	ZeroMemory(&m_ThostFtdcSyncingInstrumentTradingRightField, sizeof(m_ThostFtdcSyncingInstrumentTradingRightField));
	ZeroMemory(&m_ThostFtdcQryOrderField, sizeof(m_ThostFtdcQryOrderField));
	ZeroMemory(&m_ThostFtdcQryTradeField, sizeof(m_ThostFtdcQryTradeField));
	ZeroMemory(&m_ThostFtdcQryInvestorPositionField, sizeof(m_ThostFtdcQryInvestorPositionField));
	ZeroMemory(&m_ThostFtdcQryTradingAccountField, sizeof(m_ThostFtdcQryTradingAccountField));
	ZeroMemory(&m_ThostFtdcQryInvestorField, sizeof(m_ThostFtdcQryInvestorField));
	ZeroMemory(&m_ThostFtdcQryTradingCodeField, sizeof(m_ThostFtdcQryTradingCodeField));
	ZeroMemory(&m_ThostFtdcQryInvestorGroupField, sizeof(m_ThostFtdcQryInvestorGroupField));
	ZeroMemory(&m_ThostFtdcQryInstrumentMarginRateField, sizeof(m_ThostFtdcQryInstrumentMarginRateField));
	ZeroMemory(&m_ThostFtdcQryInstrumentCommissionRateField, sizeof(m_ThostFtdcQryInstrumentCommissionRateField));
	ZeroMemory(&m_ThostFtdcQryInstrumentTradingRightField, sizeof(m_ThostFtdcQryInstrumentTradingRightField));
	ZeroMemory(&m_ThostFtdcQryBrokerField, sizeof(m_ThostFtdcQryBrokerField));
	ZeroMemory(&m_ThostFtdcQryTraderField, sizeof(m_ThostFtdcQryTraderField));
	ZeroMemory(&m_ThostFtdcQrySuperUserFunctionField, sizeof(m_ThostFtdcQrySuperUserFunctionField));
	ZeroMemory(&m_ThostFtdcQryUserSessionField, sizeof(m_ThostFtdcQryUserSessionField));
	ZeroMemory(&m_ThostFtdcQryPartBrokerField, sizeof(m_ThostFtdcQryPartBrokerField));
	ZeroMemory(&m_ThostFtdcQryFrontStatusField, sizeof(m_ThostFtdcQryFrontStatusField));
	ZeroMemory(&m_ThostFtdcQryExchangeOrderField, sizeof(m_ThostFtdcQryExchangeOrderField));
	ZeroMemory(&m_ThostFtdcQryOrderActionField, sizeof(m_ThostFtdcQryOrderActionField));
	ZeroMemory(&m_ThostFtdcQryExchangeOrderActionField, sizeof(m_ThostFtdcQryExchangeOrderActionField));
	ZeroMemory(&m_ThostFtdcQrySuperUserField, sizeof(m_ThostFtdcQrySuperUserField));
	ZeroMemory(&m_ThostFtdcQryExchangeField, sizeof(m_ThostFtdcQryExchangeField));
	ZeroMemory(&m_ThostFtdcQryProductField, sizeof(m_ThostFtdcQryProductField));
	ZeroMemory(&m_ThostFtdcQryInstrumentField, sizeof(m_ThostFtdcQryInstrumentField));
	ZeroMemory(&m_ThostFtdcQryDepthMarketDataField, sizeof(m_ThostFtdcQryDepthMarketDataField));
	ZeroMemory(&m_ThostFtdcQryBrokerUserField, sizeof(m_ThostFtdcQryBrokerUserField));
	ZeroMemory(&m_ThostFtdcQryBrokerUserFunctionField, sizeof(m_ThostFtdcQryBrokerUserFunctionField));
	ZeroMemory(&m_ThostFtdcQryTraderOfferField, sizeof(m_ThostFtdcQryTraderOfferField));
	ZeroMemory(&m_ThostFtdcQrySyncDepositField, sizeof(m_ThostFtdcQrySyncDepositField));
	ZeroMemory(&m_ThostFtdcQrySettlementInfoField, sizeof(m_ThostFtdcQrySettlementInfoField));
	ZeroMemory(&m_ThostFtdcQryExchangeMarginRateField, sizeof(m_ThostFtdcQryExchangeMarginRateField));
	ZeroMemory(&m_ThostFtdcQryExchangeMarginRateAdjustField, sizeof(m_ThostFtdcQryExchangeMarginRateAdjustField));
	ZeroMemory(&m_ThostFtdcQryExchangeRateField, sizeof(m_ThostFtdcQryExchangeRateField));
	ZeroMemory(&m_ThostFtdcQrySyncFundMortgageField, sizeof(m_ThostFtdcQrySyncFundMortgageField));
	ZeroMemory(&m_ThostFtdcQryHisOrderField, sizeof(m_ThostFtdcQryHisOrderField));
	ZeroMemory(&m_ThostFtdcOptionInstrMiniMarginField, sizeof(m_ThostFtdcOptionInstrMiniMarginField));
	ZeroMemory(&m_ThostFtdcOptionInstrMarginAdjustField, sizeof(m_ThostFtdcOptionInstrMarginAdjustField));
	ZeroMemory(&m_ThostFtdcOptionInstrCommRateField, sizeof(m_ThostFtdcOptionInstrCommRateField));
	ZeroMemory(&m_ThostFtdcOptionInstrTradeCostField, sizeof(m_ThostFtdcOptionInstrTradeCostField));
	ZeroMemory(&m_ThostFtdcQryOptionInstrTradeCostField, sizeof(m_ThostFtdcQryOptionInstrTradeCostField));
	ZeroMemory(&m_ThostFtdcQryOptionInstrCommRateField, sizeof(m_ThostFtdcQryOptionInstrCommRateField));
	ZeroMemory(&m_ThostFtdcIndexPriceField, sizeof(m_ThostFtdcIndexPriceField));
	ZeroMemory(&m_ThostFtdcInputExecOrderField, sizeof(m_ThostFtdcInputExecOrderField));
	ZeroMemory(&m_ThostFtdcInputExecOrderActionField, sizeof(m_ThostFtdcInputExecOrderActionField));
	ZeroMemory(&m_ThostFtdcExecOrderField, sizeof(m_ThostFtdcExecOrderField));
	ZeroMemory(&m_ThostFtdcExecOrderActionField, sizeof(m_ThostFtdcExecOrderActionField));
	ZeroMemory(&m_ThostFtdcQryExecOrderField, sizeof(m_ThostFtdcQryExecOrderField));
	ZeroMemory(&m_ThostFtdcExchangeExecOrderField, sizeof(m_ThostFtdcExchangeExecOrderField));
	ZeroMemory(&m_ThostFtdcQryExchangeExecOrderField, sizeof(m_ThostFtdcQryExchangeExecOrderField));
	ZeroMemory(&m_ThostFtdcQryExecOrderActionField, sizeof(m_ThostFtdcQryExecOrderActionField));
	ZeroMemory(&m_ThostFtdcExchangeExecOrderActionField, sizeof(m_ThostFtdcExchangeExecOrderActionField));
	ZeroMemory(&m_ThostFtdcQryExchangeExecOrderActionField, sizeof(m_ThostFtdcQryExchangeExecOrderActionField));
	ZeroMemory(&m_ThostFtdcErrExecOrderField, sizeof(m_ThostFtdcErrExecOrderField));
	ZeroMemory(&m_ThostFtdcQryErrExecOrderField, sizeof(m_ThostFtdcQryErrExecOrderField));
	ZeroMemory(&m_ThostFtdcErrExecOrderActionField, sizeof(m_ThostFtdcErrExecOrderActionField));
	ZeroMemory(&m_ThostFtdcQryErrExecOrderActionField, sizeof(m_ThostFtdcQryErrExecOrderActionField));
	ZeroMemory(&m_ThostFtdcOptionInstrTradingRightField, sizeof(m_ThostFtdcOptionInstrTradingRightField));
	ZeroMemory(&m_ThostFtdcQryOptionInstrTradingRightField, sizeof(m_ThostFtdcQryOptionInstrTradingRightField));
	ZeroMemory(&m_ThostFtdcInputForQuoteField, sizeof(m_ThostFtdcInputForQuoteField));
	ZeroMemory(&m_ThostFtdcForQuoteField, sizeof(m_ThostFtdcForQuoteField));
	ZeroMemory(&m_ThostFtdcQryForQuoteField, sizeof(m_ThostFtdcQryForQuoteField));
	ZeroMemory(&m_ThostFtdcExchangeForQuoteField, sizeof(m_ThostFtdcExchangeForQuoteField));
	ZeroMemory(&m_ThostFtdcQryExchangeForQuoteField, sizeof(m_ThostFtdcQryExchangeForQuoteField));
	ZeroMemory(&m_ThostFtdcInputQuoteField, sizeof(m_ThostFtdcInputQuoteField));
	ZeroMemory(&m_ThostFtdcInputQuoteActionField, sizeof(m_ThostFtdcInputQuoteActionField));
	ZeroMemory(&m_ThostFtdcQuoteField, sizeof(m_ThostFtdcQuoteField));
	ZeroMemory(&m_ThostFtdcQuoteActionField, sizeof(m_ThostFtdcQuoteActionField));
	ZeroMemory(&m_ThostFtdcQryQuoteField, sizeof(m_ThostFtdcQryQuoteField));
	ZeroMemory(&m_ThostFtdcExchangeQuoteField, sizeof(m_ThostFtdcExchangeQuoteField));
	ZeroMemory(&m_ThostFtdcQryExchangeQuoteField, sizeof(m_ThostFtdcQryExchangeQuoteField));
	ZeroMemory(&m_ThostFtdcQryQuoteActionField, sizeof(m_ThostFtdcQryQuoteActionField));
	ZeroMemory(&m_ThostFtdcExchangeQuoteActionField, sizeof(m_ThostFtdcExchangeQuoteActionField));
	ZeroMemory(&m_ThostFtdcQryExchangeQuoteActionField, sizeof(m_ThostFtdcQryExchangeQuoteActionField));
	ZeroMemory(&m_ThostFtdcOptionInstrDeltaField, sizeof(m_ThostFtdcOptionInstrDeltaField));
	ZeroMemory(&m_ThostFtdcForQuoteRspField, sizeof(m_ThostFtdcForQuoteRspField));
	ZeroMemory(&m_ThostFtdcStrikeOffsetField, sizeof(m_ThostFtdcStrikeOffsetField));
	ZeroMemory(&m_ThostFtdcQryStrikeOffsetField, sizeof(m_ThostFtdcQryStrikeOffsetField));
	ZeroMemory(&m_ThostFtdcMarketDataField, sizeof(m_ThostFtdcMarketDataField));
	ZeroMemory(&m_ThostFtdcMarketDataBaseField, sizeof(m_ThostFtdcMarketDataBaseField));
	ZeroMemory(&m_ThostFtdcMarketDataStaticField, sizeof(m_ThostFtdcMarketDataStaticField));
	ZeroMemory(&m_ThostFtdcMarketDataLastMatchField, sizeof(m_ThostFtdcMarketDataLastMatchField));
	ZeroMemory(&m_ThostFtdcMarketDataBestPriceField, sizeof(m_ThostFtdcMarketDataBestPriceField));
	ZeroMemory(&m_ThostFtdcMarketDataBid23Field, sizeof(m_ThostFtdcMarketDataBid23Field));
	ZeroMemory(&m_ThostFtdcMarketDataAsk23Field, sizeof(m_ThostFtdcMarketDataAsk23Field));
	ZeroMemory(&m_ThostFtdcMarketDataBid45Field, sizeof(m_ThostFtdcMarketDataBid45Field));
	ZeroMemory(&m_ThostFtdcMarketDataAsk45Field, sizeof(m_ThostFtdcMarketDataAsk45Field));
	ZeroMemory(&m_ThostFtdcMarketDataUpdateTimeField, sizeof(m_ThostFtdcMarketDataUpdateTimeField));
	ZeroMemory(&m_ThostFtdcMarketDataExchangeField, sizeof(m_ThostFtdcMarketDataExchangeField));
	ZeroMemory(&m_ThostFtdcSpecificInstrumentField, sizeof(m_ThostFtdcSpecificInstrumentField));
	ZeroMemory(&m_ThostFtdcInstrumentStatusField, sizeof(m_ThostFtdcInstrumentStatusField));
	ZeroMemory(&m_ThostFtdcQryInstrumentStatusField, sizeof(m_ThostFtdcQryInstrumentStatusField));
	ZeroMemory(&m_ThostFtdcInvestorAccountField, sizeof(m_ThostFtdcInvestorAccountField));
	ZeroMemory(&m_ThostFtdcPositionProfitAlgorithmField, sizeof(m_ThostFtdcPositionProfitAlgorithmField));
	ZeroMemory(&m_ThostFtdcDiscountField, sizeof(m_ThostFtdcDiscountField));
	ZeroMemory(&m_ThostFtdcQryTransferBankField, sizeof(m_ThostFtdcQryTransferBankField));
	ZeroMemory(&m_ThostFtdcTransferBankField, sizeof(m_ThostFtdcTransferBankField));
	ZeroMemory(&m_ThostFtdcQryInvestorPositionDetailField, sizeof(m_ThostFtdcQryInvestorPositionDetailField));
	ZeroMemory(&m_ThostFtdcInvestorPositionDetailField, sizeof(m_ThostFtdcInvestorPositionDetailField));
	ZeroMemory(&m_ThostFtdcTradingAccountPasswordField, sizeof(m_ThostFtdcTradingAccountPasswordField));
	ZeroMemory(&m_ThostFtdcMDTraderOfferField, sizeof(m_ThostFtdcMDTraderOfferField));
	ZeroMemory(&m_ThostFtdcQryMDTraderOfferField, sizeof(m_ThostFtdcQryMDTraderOfferField));
	ZeroMemory(&m_ThostFtdcQryNoticeField, sizeof(m_ThostFtdcQryNoticeField));
	ZeroMemory(&m_ThostFtdcNoticeField, sizeof(m_ThostFtdcNoticeField));
	ZeroMemory(&m_ThostFtdcUserRightField, sizeof(m_ThostFtdcUserRightField));
	ZeroMemory(&m_ThostFtdcQrySettlementInfoConfirmField, sizeof(m_ThostFtdcQrySettlementInfoConfirmField));
	ZeroMemory(&m_ThostFtdcLoadSettlementInfoField, sizeof(m_ThostFtdcLoadSettlementInfoField));
	ZeroMemory(&m_ThostFtdcBrokerWithdrawAlgorithmField, sizeof(m_ThostFtdcBrokerWithdrawAlgorithmField));
	ZeroMemory(&m_ThostFtdcTradingAccountPasswordUpdateV1Field, sizeof(m_ThostFtdcTradingAccountPasswordUpdateV1Field));
	ZeroMemory(&m_ThostFtdcTradingAccountPasswordUpdateField, sizeof(m_ThostFtdcTradingAccountPasswordUpdateField));
	ZeroMemory(&m_ThostFtdcQryCombinationLegField, sizeof(m_ThostFtdcQryCombinationLegField));
	ZeroMemory(&m_ThostFtdcQrySyncStatusField, sizeof(m_ThostFtdcQrySyncStatusField));
	ZeroMemory(&m_ThostFtdcCombinationLegField, sizeof(m_ThostFtdcCombinationLegField));
	ZeroMemory(&m_ThostFtdcSyncStatusField, sizeof(m_ThostFtdcSyncStatusField));
	ZeroMemory(&m_ThostFtdcQryLinkManField, sizeof(m_ThostFtdcQryLinkManField));
	ZeroMemory(&m_ThostFtdcLinkManField, sizeof(m_ThostFtdcLinkManField));
	ZeroMemory(&m_ThostFtdcQryBrokerUserEventField, sizeof(m_ThostFtdcQryBrokerUserEventField));
	ZeroMemory(&m_ThostFtdcBrokerUserEventField, sizeof(m_ThostFtdcBrokerUserEventField));
	ZeroMemory(&m_ThostFtdcQryContractBankField, sizeof(m_ThostFtdcQryContractBankField));
	ZeroMemory(&m_ThostFtdcContractBankField, sizeof(m_ThostFtdcContractBankField));
	ZeroMemory(&m_ThostFtdcInvestorPositionCombineDetailField, sizeof(m_ThostFtdcInvestorPositionCombineDetailField));
	ZeroMemory(&m_ThostFtdcParkedOrderField, sizeof(m_ThostFtdcParkedOrderField));
	ZeroMemory(&m_ThostFtdcParkedOrderActionField, sizeof(m_ThostFtdcParkedOrderActionField));
	ZeroMemory(&m_ThostFtdcQryParkedOrderField, sizeof(m_ThostFtdcQryParkedOrderField));
	ZeroMemory(&m_ThostFtdcQryParkedOrderActionField, sizeof(m_ThostFtdcQryParkedOrderActionField));
	ZeroMemory(&m_ThostFtdcRemoveParkedOrderField, sizeof(m_ThostFtdcRemoveParkedOrderField));
	ZeroMemory(&m_ThostFtdcRemoveParkedOrderActionField, sizeof(m_ThostFtdcRemoveParkedOrderActionField));
	ZeroMemory(&m_ThostFtdcInvestorWithdrawAlgorithmField, sizeof(m_ThostFtdcInvestorWithdrawAlgorithmField));
	ZeroMemory(&m_ThostFtdcQryInvestorPositionCombineDetailField, sizeof(m_ThostFtdcQryInvestorPositionCombineDetailField));
	ZeroMemory(&m_ThostFtdcMarketDataAveragePriceField, sizeof(m_ThostFtdcMarketDataAveragePriceField));
	ZeroMemory(&m_ThostFtdcVerifyInvestorPasswordField, sizeof(m_ThostFtdcVerifyInvestorPasswordField));
	ZeroMemory(&m_ThostFtdcUserIPField, sizeof(m_ThostFtdcUserIPField));
	ZeroMemory(&m_ThostFtdcTradingNoticeInfoField, sizeof(m_ThostFtdcTradingNoticeInfoField));
	ZeroMemory(&m_ThostFtdcTradingNoticeField, sizeof(m_ThostFtdcTradingNoticeField));
	ZeroMemory(&m_ThostFtdcQryTradingNoticeField, sizeof(m_ThostFtdcQryTradingNoticeField));
	ZeroMemory(&m_ThostFtdcQryErrOrderField, sizeof(m_ThostFtdcQryErrOrderField));
	ZeroMemory(&m_ThostFtdcErrOrderField, sizeof(m_ThostFtdcErrOrderField));
	ZeroMemory(&m_ThostFtdcErrorConditionalOrderField, sizeof(m_ThostFtdcErrorConditionalOrderField));
	ZeroMemory(&m_ThostFtdcQryErrOrderActionField, sizeof(m_ThostFtdcQryErrOrderActionField));
	ZeroMemory(&m_ThostFtdcErrOrderActionField, sizeof(m_ThostFtdcErrOrderActionField));
	ZeroMemory(&m_ThostFtdcQryExchangeSequenceField, sizeof(m_ThostFtdcQryExchangeSequenceField));
	ZeroMemory(&m_ThostFtdcExchangeSequenceField, sizeof(m_ThostFtdcExchangeSequenceField));
	ZeroMemory(&m_ThostFtdcQueryMaxOrderVolumeWithPriceField, sizeof(m_ThostFtdcQueryMaxOrderVolumeWithPriceField));
	ZeroMemory(&m_ThostFtdcQryBrokerTradingParamsField, sizeof(m_ThostFtdcQryBrokerTradingParamsField));
	ZeroMemory(&m_ThostFtdcBrokerTradingParamsField, sizeof(m_ThostFtdcBrokerTradingParamsField));
	ZeroMemory(&m_ThostFtdcQryBrokerTradingAlgosField, sizeof(m_ThostFtdcQryBrokerTradingAlgosField));
	ZeroMemory(&m_ThostFtdcBrokerTradingAlgosField, sizeof(m_ThostFtdcBrokerTradingAlgosField));
	ZeroMemory(&m_ThostFtdcQueryBrokerDepositField, sizeof(m_ThostFtdcQueryBrokerDepositField));
	ZeroMemory(&m_ThostFtdcBrokerDepositField, sizeof(m_ThostFtdcBrokerDepositField));
	ZeroMemory(&m_ThostFtdcQryCFMMCBrokerKeyField, sizeof(m_ThostFtdcQryCFMMCBrokerKeyField));
	ZeroMemory(&m_ThostFtdcCFMMCBrokerKeyField, sizeof(m_ThostFtdcCFMMCBrokerKeyField));
	ZeroMemory(&m_ThostFtdcCFMMCTradingAccountKeyField, sizeof(m_ThostFtdcCFMMCTradingAccountKeyField));
	ZeroMemory(&m_ThostFtdcQryCFMMCTradingAccountKeyField, sizeof(m_ThostFtdcQryCFMMCTradingAccountKeyField));
	ZeroMemory(&m_ThostFtdcBrokerUserOTPParamField, sizeof(m_ThostFtdcBrokerUserOTPParamField));
	ZeroMemory(&m_ThostFtdcManualSyncBrokerUserOTPField, sizeof(m_ThostFtdcManualSyncBrokerUserOTPField));
	ZeroMemory(&m_ThostFtdcCommRateModelField, sizeof(m_ThostFtdcCommRateModelField));
	ZeroMemory(&m_ThostFtdcQryCommRateModelField, sizeof(m_ThostFtdcQryCommRateModelField));
	ZeroMemory(&m_ThostFtdcMarginModelField, sizeof(m_ThostFtdcMarginModelField));
	ZeroMemory(&m_ThostFtdcQryMarginModelField, sizeof(m_ThostFtdcQryMarginModelField));
	ZeroMemory(&m_ThostFtdcEWarrantOffsetField, sizeof(m_ThostFtdcEWarrantOffsetField));
	ZeroMemory(&m_ThostFtdcQryEWarrantOffsetField, sizeof(m_ThostFtdcQryEWarrantOffsetField));
	ZeroMemory(&m_ThostFtdcQryInvestorProductGroupMarginField, sizeof(m_ThostFtdcQryInvestorProductGroupMarginField));
	ZeroMemory(&m_ThostFtdcInvestorProductGroupMarginField, sizeof(m_ThostFtdcInvestorProductGroupMarginField));
	ZeroMemory(&m_ThostFtdcReqOpenAccountField, sizeof(m_ThostFtdcReqOpenAccountField));
	ZeroMemory(&m_ThostFtdcReqCancelAccountField, sizeof(m_ThostFtdcReqCancelAccountField));
	ZeroMemory(&m_ThostFtdcReqChangeAccountField, sizeof(m_ThostFtdcReqChangeAccountField));
	ZeroMemory(&m_ThostFtdcReqTransferField, sizeof(m_ThostFtdcReqTransferField));
	ZeroMemory(&m_ThostFtdcRspTransferField, sizeof(m_ThostFtdcRspTransferField));
	ZeroMemory(&m_ThostFtdcReqRepealField, sizeof(m_ThostFtdcReqRepealField));
	ZeroMemory(&m_ThostFtdcRspRepealField, sizeof(m_ThostFtdcRspRepealField));
	ZeroMemory(&m_ThostFtdcReqQueryAccountField, sizeof(m_ThostFtdcReqQueryAccountField));
	ZeroMemory(&m_ThostFtdcRspQueryAccountField, sizeof(m_ThostFtdcRspQueryAccountField));
	ZeroMemory(&m_ThostFtdcFutureSignIOField, sizeof(m_ThostFtdcFutureSignIOField));
	ZeroMemory(&m_ThostFtdcRspFutureSignInField, sizeof(m_ThostFtdcRspFutureSignInField));
	ZeroMemory(&m_ThostFtdcReqFutureSignOutField, sizeof(m_ThostFtdcReqFutureSignOutField));
	ZeroMemory(&m_ThostFtdcRspFutureSignOutField, sizeof(m_ThostFtdcRspFutureSignOutField));
	ZeroMemory(&m_ThostFtdcReqQueryTradeResultBySerialField, sizeof(m_ThostFtdcReqQueryTradeResultBySerialField));
	ZeroMemory(&m_ThostFtdcRspQueryTradeResultBySerialField, sizeof(m_ThostFtdcRspQueryTradeResultBySerialField));
	ZeroMemory(&m_ThostFtdcReqDayEndFileReadyField, sizeof(m_ThostFtdcReqDayEndFileReadyField));
	ZeroMemory(&m_ThostFtdcReturnResultField, sizeof(m_ThostFtdcReturnResultField));
	ZeroMemory(&m_ThostFtdcVerifyFuturePasswordField, sizeof(m_ThostFtdcVerifyFuturePasswordField));
	ZeroMemory(&m_ThostFtdcVerifyCustInfoField, sizeof(m_ThostFtdcVerifyCustInfoField));
	ZeroMemory(&m_ThostFtdcVerifyFuturePasswordAndCustInfoField, sizeof(m_ThostFtdcVerifyFuturePasswordAndCustInfoField));
	ZeroMemory(&m_ThostFtdcDepositResultInformField, sizeof(m_ThostFtdcDepositResultInformField));
	ZeroMemory(&m_ThostFtdcReqSyncKeyField, sizeof(m_ThostFtdcReqSyncKeyField));
	ZeroMemory(&m_ThostFtdcRspSyncKeyField, sizeof(m_ThostFtdcRspSyncKeyField));
	ZeroMemory(&m_ThostFtdcNotifyQueryAccountField, sizeof(m_ThostFtdcNotifyQueryAccountField));
	ZeroMemory(&m_ThostFtdcTransferSerialField, sizeof(m_ThostFtdcTransferSerialField));
	ZeroMemory(&m_ThostFtdcQryTransferSerialField, sizeof(m_ThostFtdcQryTransferSerialField));
	ZeroMemory(&m_ThostFtdcNotifyFutureSignInField, sizeof(m_ThostFtdcNotifyFutureSignInField));
	ZeroMemory(&m_ThostFtdcNotifyFutureSignOutField, sizeof(m_ThostFtdcNotifyFutureSignOutField));
	ZeroMemory(&m_ThostFtdcNotifySyncKeyField, sizeof(m_ThostFtdcNotifySyncKeyField));
	ZeroMemory(&m_ThostFtdcQryAccountregisterField, sizeof(m_ThostFtdcQryAccountregisterField));
	ZeroMemory(&m_ThostFtdcAccountregisterField, sizeof(m_ThostFtdcAccountregisterField));
	ZeroMemory(&m_ThostFtdcOpenAccountField, sizeof(m_ThostFtdcOpenAccountField));
	ZeroMemory(&m_ThostFtdcCancelAccountField, sizeof(m_ThostFtdcCancelAccountField));
	ZeroMemory(&m_ThostFtdcChangeAccountField, sizeof(m_ThostFtdcChangeAccountField));
	ZeroMemory(&m_ThostFtdcSecAgentACIDMapField, sizeof(m_ThostFtdcSecAgentACIDMapField));
	ZeroMemory(&m_ThostFtdcQrySecAgentACIDMapField, sizeof(m_ThostFtdcQrySecAgentACIDMapField));
	ZeroMemory(&m_ThostFtdcUserRightsAssignField, sizeof(m_ThostFtdcUserRightsAssignField));
	ZeroMemory(&m_ThostFtdcBrokerUserRightAssignField, sizeof(m_ThostFtdcBrokerUserRightAssignField));
	ZeroMemory(&m_ThostFtdcDRTransferField, sizeof(m_ThostFtdcDRTransferField));
	ZeroMemory(&m_ThostFtdcFensUserInfoField, sizeof(m_ThostFtdcFensUserInfoField));
	ZeroMemory(&m_ThostFtdcCurrTransferIdentityField, sizeof(m_ThostFtdcCurrTransferIdentityField));
	ZeroMemory(&m_ThostFtdcLoginForbiddenUserField, sizeof(m_ThostFtdcLoginForbiddenUserField));
	ZeroMemory(&m_ThostFtdcQryLoginForbiddenUserField, sizeof(m_ThostFtdcQryLoginForbiddenUserField));
	ZeroMemory(&m_ThostFtdcMulticastGroupInfoField, sizeof(m_ThostFtdcMulticastGroupInfoField));
	ZeroMemory(&m_ThostFtdcTradingAccountReserveField, sizeof(m_ThostFtdcTradingAccountReserveField));
}

void CFemasTHelper::InitTypes()
{
	RegType("TThostFtdcDateType","char", "", 9);
	RegType("TThostFtdcUserIDType","char", "", 16);
	RegType("TThostFtdcBrokerIDType","char", "", 11);
	RegType("TThostFtdcPasswordType","char", "", 41);
	RegType("TThostFtdcProductInfoType","char", "", 41);
	RegType("TThostFtdcProtocolInfoType","char", "", 41);
	RegType("TThostFtdcIPAddressType","char", "", 21);
	RegType("TThostFtdcMacAddressType","char", "", 21);
	RegType("TThostFtdcDataCenterIDType","int");
	RegType("TThostFtdcTimeType", "char", "", 9);
	RegType("TThostFtdcUserOrderLocalIDType", "char", "", 21);
	RegType("TThostFtdcTradingSystemNameType", "char", "", 61);
	RegType("TThostFtdcSequenceNoType","int");
	RegType("TThostFtdcErrorIDType","int");
	RegType("TThostFtdcErrorMsgType","char","",81);
	RegType("TThostFtdcExchangeIDType","char","",11);
	RegType("TThostFtdcOrderSysIDType","char","",31);
	RegType("TThostFtdcInvestorIDType","char","",19);
	RegType("TThostFtdcInstrumentIDType","char","",31);
	RegType("TThostFtdcOrderPriceTypeType","list","任意价:Thost_FTDC_OPT_AnyPrice:1,限价:Thost_FTDC_OPT_LimitPrice:2");
	RegType("TThostFtdcDirectionType","list","买:Thost_FTDC_D_Buy:0,卖:Thost_FTDC_D_Sell:1");
	RegType("TThostFtdcOffsetFlagType","list","开仓:Thost_FTDC_OF_Open:0,平仓:Thost_FTDC_OF_Close:1,强平:Thost_FTDC_OF_ForceClose:2,平今:Thost_FTDC_OF_CloseToday:3,平昨:Thost_FTDC_OF_CloseYesterday:4");
	RegType("TThostFtdcHedgeFlagType","list","投机:Thost_FTDC_CHF_Speculation:1,套利:Thost_FTDC_CHF_Arbitrage:2,套保:Thost_FTDC_CHF_Hedge:3");
	RegType("TThostFtdcPriceType","double");
	RegType("TThostFtdcVolumeType","int");
	RegType("TThostFtdcTimeConditionType","list","立即完成否则撤销:Thost_FTDC_TC_IOC:1,本节有效:Thost_FTDC_TC_GFS:2,当日有效:Thost_FTDC_TC_GFD:3,指定日期前有效:Thost_FTDC_TC_GTD:4,撤销前有效:Thost_FTDC_TC_GTC:5,集合竞价有效:Thost_FTDC_TC_GFA:6");
	RegType("TThostFtdcVolumeConditionType","list","任何数量:Thost_FTDC_VC_AV:1,最小数量:Thost_FTDC_VC_MV:2,全部数量:Thost_FTDC_VC_CV:3");
	RegType("TThostFtdcForceCloseReasonType","list","非强平:Thost_FTDC_FCR_NotForceClose:0,资金不足:Thost_FTDC_FCR_LackDeposit:1,客户超仓:Thost_FTDC_FCR_ClientOverPositionLimit:2,会员超仓:Thost_FTDC_FCR_MemberOverPositionLimit:3,持仓非整数倍:Thost_FTDC_FCR_NotMultiple:4");
	RegType("TThostFtdcBoolType","int");
	RegType("TThostFtdcBusinessUnitType","char","",21);
	RegType("TThostFtdcCustomType","char","",65);
	RegType("TThostFtdcTradingDayType","char","",9);
	RegType("TThostFtdcParticipantIDType","char","",11);
	RegType("TThostFtdcClientIDType","char","",19);
	RegType("TThostFtdcSeatIDType","char","",13);
	RegType("TThostFtdcOrderLocalIDType","char","",13);
	RegType("TThostFtdcOrderSourceType","list","来自参与者:Thost_FTDC_OS_Participant:0,来自管理员:Thost_FTDC_OS_Administrator:1");
	RegType("TThostFtdcOrderSourceType","list","来自参与者:Thost_FTDC_OS_Participant:0,来自管理员:Thost_FTDC_OS_Administrator:1");
	RegType("TThostFtdcOrderStatusType","list","全部成交:Thost_FTDC_OS_AllTraded:0,部分成交还在队列中:Thost_FTDC_OS_PartTradedQueueing:1,部分成交不在队列中:Thost_FTDC_OS_PartTradedNotQueueing:2,未成交还在队列中:Thost_FTDC_OS_NoTradeQueueing:3,未成交不在队列中:Thost_FTDC_OS_NoTradeNotQueueing:4,撤单:Thost_FTDC_OS_Canceled:5");
	RegType("TThostFtdcTradeIDType","char","",21);
}

void CFemasTHelper::RegType( std::string name, std::string ftype, std::string lstr /*= ""*/, int len /*= 0 */ )
{
	Type t;
	t.name = name;
	t.ftype = ftype;
	t.len = len;

	std::vector<std::string> sel_str;
	boost::split(sel_str, lstr, boost::is_any_of(","));

	for(auto it = sel_str.begin(); it != sel_str.end(); ++it)
	{
		std::vector<std::string> sel_info_str;
		boost::split(sel_info_str, *it, boost::is_any_of(":"));
		t.lstrs.push_back(sel_info_str);
	}

	m_Types[name] = t;
}

void CFemasTHelper::RegField( std::string str, std::string name, std::string type, std::string fname, void *ptr, std::string val /*="" */ )
{
	Field f;
	f.str = str;
	f.name = name;
	f.type = type;
	f.fname = fname;
	f.val = val;
	f.ptr = ptr;
	f.label_wnd = f.h_wnd = NULL;
	m_Fields[str].push_back(f);
}

void CFemasTHelper::RegFun( int id, std::string name, std::function<int(int)>& func, std::string field, std::string filed2 /*= ""*/ )
{
	Func fun;
	fun.func = func;
	fun.param1 = field;
	fun.parma2 = filed2;
	fun.fname = name;
	m_FemasReqFuncs[id] = fun;
	std::string ttype;
	std::string tfield = field;
	int n = 0;
	while(m_Fields.find(tfield) != m_Fields.end())
	{
		std::vector<Field> &fields = m_Fields[tfield];

		for (auto it = fields.begin(); it != fields.end(); ++it)
		{
			if (it->h_wnd)
			{
				delete it->h_wnd;
				it->h_wnd = NULL;
			}
			if (it->label_wnd)
			{
				delete it->label_wnd;
				it->label_wnd = NULL;
			}

			ttype = m_Types[it->type].ftype;
			int x = (n/9) * 260 + 230;
			int y = (n%9) * 40 + 12;
			CRect rc(x,y-12,x+120,y+27);
			CRect rc2(x+125,y,x+230,y+25);

			HWND hLabel = ::CreateWindow("STATIC", "", WS_CHILD  ,
				x, y-2, 120, 27, *m_pMainDlg, NULL, GetModuleHandle(NULL), NULL);
			DWORD dw = GetLastError();
			::SetWindowText(hLabel,(it->name+"\r\n("+it->fname+"):").c_str());
			CStatic *label=new CStatic(hLabel);
			it->label_wnd = (CWindow*)label;
			label->SetFont(*m_pMainDlg->m_pFont);

			if (ttype == "list")
			{
				HWND hCombo = ::CreateWindow("COMBOBOX", "", WS_CHILD|WS_VSCROLL|CBS_DROPDOWNLIST,
					x+125, y, 105, 25, *m_pMainDlg, NULL, GetModuleHandle(NULL), NULL);
				CComboBox *combo=new CComboBox (hCombo);
				for (auto itList = m_Types[it->type].lstrs.begin(); itList != m_Types[it->type].lstrs.end(); ++itList)
				{
					combo->AddString((*itList)[0].c_str());
				}
				combo->SetFont(*m_pMainDlg->m_pFont);
				combo->SetCurSel(0);
				it->h_wnd = combo;
			}
			else
			{
				HWND hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD  | WS_TABSTOP | ES_AUTOHSCROLL
					, x+125, y, 105, 25, *m_pMainDlg, NULL, GetModuleHandle(NULL), NULL);
				CEdit *edit = new CEdit(hEdit);
				edit->SetFont(*m_pMainDlg->m_pFont);

				if (ttype == "char")
				{
					edit->SetLimitText(m_Types[it->type].len);
				}
				else if (ttype == "double")
				{
					edit->SetLimitText(25);
					edit->SetWindowText("0.0");
				}
				else
				{
					edit->SetLimitText(12);
					edit->SetWindowText("0");
				}

				it->h_wnd = edit;
			}
			n++;
		}
		if (tfield != filed2) tfield = filed2; else break;
	}
}


void CFemasTHelper::InitFields()
{
	RegField("CThostFtdcDisseminationField","序列系列号","TThostFtdcSequenceSeriesType", "SequenceSeries", &(m_ThostFtdcDisseminationField.SequenceSeries));
	RegField("CThostFtdcDisseminationField","序列号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcDisseminationField.SequenceNo));

	RegField("CThostFtdcReqUserLoginField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcReqUserLoginField.TradingDay));
	RegField("CThostFtdcReqUserLoginField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqUserLoginField.BrokerID));
	RegField("CThostFtdcReqUserLoginField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqUserLoginField.UserID));
	RegField("CThostFtdcReqUserLoginField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqUserLoginField.Password));
	RegField("CThostFtdcReqUserLoginField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcReqUserLoginField.UserProductInfo));
	RegField("CThostFtdcReqUserLoginField","接口端产品信息","TThostFtdcProductInfoType", "InterfaceProductInfo", &(m_ThostFtdcReqUserLoginField.InterfaceProductInfo));
	RegField("CThostFtdcReqUserLoginField","协议信息","TThostFtdcProtocolInfoType", "ProtocolInfo", &(m_ThostFtdcReqUserLoginField.ProtocolInfo));
	RegField("CThostFtdcReqUserLoginField","Mac地址","TThostFtdcMacAddressType", "MacAddress", &(m_ThostFtdcReqUserLoginField.MacAddress));
	RegField("CThostFtdcReqUserLoginField","动态密码","TThostFtdcPasswordType", "OneTimePassword", &(m_ThostFtdcReqUserLoginField.OneTimePassword));
	RegField("CThostFtdcReqUserLoginField","终端IP地址","TThostFtdcIPAddressType", "ClientIPAddress", &(m_ThostFtdcReqUserLoginField.ClientIPAddress));

	RegField("CThostFtdcRspUserLoginField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcRspUserLoginField.TradingDay));
	RegField("CThostFtdcRspUserLoginField","登录成功时间","TThostFtdcTimeType", "LoginTime", &(m_ThostFtdcRspUserLoginField.LoginTime));
	RegField("CThostFtdcRspUserLoginField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspUserLoginField.BrokerID));
	RegField("CThostFtdcRspUserLoginField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspUserLoginField.UserID));
	RegField("CThostFtdcRspUserLoginField","交易系统名称","TThostFtdcSystemNameType", "SystemName", &(m_ThostFtdcRspUserLoginField.SystemName));
	RegField("CThostFtdcRspUserLoginField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcRspUserLoginField.FrontID));
	RegField("CThostFtdcRspUserLoginField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspUserLoginField.SessionID));
	RegField("CThostFtdcRspUserLoginField","最大报单引用","TThostFtdcOrderRefType", "MaxOrderRef", &(m_ThostFtdcRspUserLoginField.MaxOrderRef));
	RegField("CThostFtdcRspUserLoginField","上期所时间","TThostFtdcTimeType", "SHFETime", &(m_ThostFtdcRspUserLoginField.SHFETime));
	RegField("CThostFtdcRspUserLoginField","大商所时间","TThostFtdcTimeType", "DCETime", &(m_ThostFtdcRspUserLoginField.DCETime));
	RegField("CThostFtdcRspUserLoginField","郑商所时间","TThostFtdcTimeType", "CZCETime", &(m_ThostFtdcRspUserLoginField.CZCETime));
	RegField("CThostFtdcRspUserLoginField","中金所时间","TThostFtdcTimeType", "FFEXTime", &(m_ThostFtdcRspUserLoginField.FFEXTime));
	RegField("CThostFtdcRspUserLoginField","能源中心时间","TThostFtdcTimeType", "INETime", &(m_ThostFtdcRspUserLoginField.INETime));

	RegField("CThostFtdcUserLogoutField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcUserLogoutField.BrokerID));
	RegField("CThostFtdcUserLogoutField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcUserLogoutField.UserID));

	RegField("CThostFtdcForceUserLogoutField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcForceUserLogoutField.BrokerID));
	RegField("CThostFtdcForceUserLogoutField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcForceUserLogoutField.UserID));

	RegField("CThostFtdcReqAuthenticateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqAuthenticateField.BrokerID));
	RegField("CThostFtdcReqAuthenticateField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqAuthenticateField.UserID));
	RegField("CThostFtdcReqAuthenticateField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcReqAuthenticateField.UserProductInfo));
	RegField("CThostFtdcReqAuthenticateField","认证码","TThostFtdcAuthCodeType", "AuthCode", &(m_ThostFtdcReqAuthenticateField.AuthCode));

	RegField("CThostFtdcRspAuthenticateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspAuthenticateField.BrokerID));
	RegField("CThostFtdcRspAuthenticateField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspAuthenticateField.UserID));
	RegField("CThostFtdcRspAuthenticateField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcRspAuthenticateField.UserProductInfo));

	RegField("CThostFtdcAuthenticationInfoField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcAuthenticationInfoField.BrokerID));
	RegField("CThostFtdcAuthenticationInfoField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcAuthenticationInfoField.UserID));
	RegField("CThostFtdcAuthenticationInfoField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcAuthenticationInfoField.UserProductInfo));
	RegField("CThostFtdcAuthenticationInfoField","认证信息","TThostFtdcAuthInfoType", "AuthInfo", &(m_ThostFtdcAuthenticationInfoField.AuthInfo));
	RegField("CThostFtdcAuthenticationInfoField","是否为认证结果","TThostFtdcBoolType", "IsResult", &(m_ThostFtdcAuthenticationInfoField.IsResult));

	RegField("CThostFtdcTransferHeaderField","版本号，常量，1","TThostFtdcVersionType", "Version", &(m_ThostFtdcTransferHeaderField.Version));
	RegField("CThostFtdcTransferHeaderField","交易代码，必填","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcTransferHeaderField.TradeCode));
	RegField("CThostFtdcTransferHeaderField","交易日期，必填，格式：yyyymmdd","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcTransferHeaderField.TradeDate));
	RegField("CThostFtdcTransferHeaderField","交易时间，必填，格式：hhmmss","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcTransferHeaderField.TradeTime));
	RegField("CThostFtdcTransferHeaderField","发起方流水号，N/A","TThostFtdcTradeSerialType", "TradeSerial", &(m_ThostFtdcTransferHeaderField.TradeSerial));
	RegField("CThostFtdcTransferHeaderField","期货公司代码，必填","TThostFtdcFutureIDType", "FutureID", &(m_ThostFtdcTransferHeaderField.FutureID));
	RegField("CThostFtdcTransferHeaderField","银行代码，根据查询银行得到，必填","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcTransferHeaderField.BankID));
	RegField("CThostFtdcTransferHeaderField","银行分中心代码，根据查询银行得到，必填","TThostFtdcBankBrchIDType", "BankBrchID", &(m_ThostFtdcTransferHeaderField.BankBrchID));
	RegField("CThostFtdcTransferHeaderField","操作员，N/A","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcTransferHeaderField.OperNo));
	RegField("CThostFtdcTransferHeaderField","交易设备类型，N/A","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcTransferHeaderField.DeviceID));
	RegField("CThostFtdcTransferHeaderField","记录数，N/A","TThostFtdcRecordNumType", "RecordNum", &(m_ThostFtdcTransferHeaderField.RecordNum));
	RegField("CThostFtdcTransferHeaderField","会话编号，N/A","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcTransferHeaderField.SessionID));
	RegField("CThostFtdcTransferHeaderField","请求编号，N/A","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcTransferHeaderField.RequestID));

	RegField("CThostFtdcTransferBankToFutureReqField","期货资金账户","TThostFtdcAccountIDType", "FutureAccount", &(m_ThostFtdcTransferBankToFutureReqField.FutureAccount));
	RegField("CThostFtdcTransferBankToFutureReqField","密码标志","TThostFtdcFuturePwdFlagType", "FuturePwdFlag", &(m_ThostFtdcTransferBankToFutureReqField.FuturePwdFlag));
	RegField("CThostFtdcTransferBankToFutureReqField","密码","TThostFtdcFutureAccPwdType", "FutureAccPwd", &(m_ThostFtdcTransferBankToFutureReqField.FutureAccPwd));
	RegField("CThostFtdcTransferBankToFutureReqField","转账金额","TThostFtdcMoneyType", "TradeAmt", &(m_ThostFtdcTransferBankToFutureReqField.TradeAmt));
	RegField("CThostFtdcTransferBankToFutureReqField","客户手续费","TThostFtdcMoneyType", "CustFee", &(m_ThostFtdcTransferBankToFutureReqField.CustFee));
	RegField("CThostFtdcTransferBankToFutureReqField","币种：RMB","TThostFtdcCurrencyCodeType", "CurrencyCode", &(m_ThostFtdcTransferBankToFutureReqField.CurrencyCode));

	RegField("CThostFtdcTransferBankToFutureRspField","响应代码","TThostFtdcRetCodeType", "RetCode", &(m_ThostFtdcTransferBankToFutureRspField.RetCode));
	RegField("CThostFtdcTransferBankToFutureRspField","响应信息","TThostFtdcRetInfoType", "RetInfo", &(m_ThostFtdcTransferBankToFutureRspField.RetInfo));
	RegField("CThostFtdcTransferBankToFutureRspField","资金账户","TThostFtdcAccountIDType", "FutureAccount", &(m_ThostFtdcTransferBankToFutureRspField.FutureAccount));
	RegField("CThostFtdcTransferBankToFutureRspField","转帐金额","TThostFtdcMoneyType", "TradeAmt", &(m_ThostFtdcTransferBankToFutureRspField.TradeAmt));
	RegField("CThostFtdcTransferBankToFutureRspField","应收客户手续费","TThostFtdcMoneyType", "CustFee", &(m_ThostFtdcTransferBankToFutureRspField.CustFee));
	RegField("CThostFtdcTransferBankToFutureRspField","币种","TThostFtdcCurrencyCodeType", "CurrencyCode", &(m_ThostFtdcTransferBankToFutureRspField.CurrencyCode));

	RegField("CThostFtdcTransferFutureToBankReqField","期货资金账户","TThostFtdcAccountIDType", "FutureAccount", &(m_ThostFtdcTransferFutureToBankReqField.FutureAccount));
	RegField("CThostFtdcTransferFutureToBankReqField","密码标志","TThostFtdcFuturePwdFlagType", "FuturePwdFlag", &(m_ThostFtdcTransferFutureToBankReqField.FuturePwdFlag));
	RegField("CThostFtdcTransferFutureToBankReqField","密码","TThostFtdcFutureAccPwdType", "FutureAccPwd", &(m_ThostFtdcTransferFutureToBankReqField.FutureAccPwd));
	RegField("CThostFtdcTransferFutureToBankReqField","转账金额","TThostFtdcMoneyType", "TradeAmt", &(m_ThostFtdcTransferFutureToBankReqField.TradeAmt));
	RegField("CThostFtdcTransferFutureToBankReqField","客户手续费","TThostFtdcMoneyType", "CustFee", &(m_ThostFtdcTransferFutureToBankReqField.CustFee));
	RegField("CThostFtdcTransferFutureToBankReqField","币种：RMB","TThostFtdcCurrencyCodeType", "CurrencyCode", &(m_ThostFtdcTransferFutureToBankReqField.CurrencyCode));

	RegField("CThostFtdcTransferFutureToBankRspField","响应代码","TThostFtdcRetCodeType", "RetCode", &(m_ThostFtdcTransferFutureToBankRspField.RetCode));
	RegField("CThostFtdcTransferFutureToBankRspField","响应信息","TThostFtdcRetInfoType", "RetInfo", &(m_ThostFtdcTransferFutureToBankRspField.RetInfo));
	RegField("CThostFtdcTransferFutureToBankRspField","资金账户","TThostFtdcAccountIDType", "FutureAccount", &(m_ThostFtdcTransferFutureToBankRspField.FutureAccount));
	RegField("CThostFtdcTransferFutureToBankRspField","转帐金额","TThostFtdcMoneyType", "TradeAmt", &(m_ThostFtdcTransferFutureToBankRspField.TradeAmt));
	RegField("CThostFtdcTransferFutureToBankRspField","应收客户手续费","TThostFtdcMoneyType", "CustFee", &(m_ThostFtdcTransferFutureToBankRspField.CustFee));
	RegField("CThostFtdcTransferFutureToBankRspField","币种","TThostFtdcCurrencyCodeType", "CurrencyCode", &(m_ThostFtdcTransferFutureToBankRspField.CurrencyCode));

	RegField("CThostFtdcTransferQryBankReqField","期货资金账户","TThostFtdcAccountIDType", "FutureAccount", &(m_ThostFtdcTransferQryBankReqField.FutureAccount));
	RegField("CThostFtdcTransferQryBankReqField","密码标志","TThostFtdcFuturePwdFlagType", "FuturePwdFlag", &(m_ThostFtdcTransferQryBankReqField.FuturePwdFlag));
	RegField("CThostFtdcTransferQryBankReqField","密码","TThostFtdcFutureAccPwdType", "FutureAccPwd", &(m_ThostFtdcTransferQryBankReqField.FutureAccPwd));
	RegField("CThostFtdcTransferQryBankReqField","币种：RMB","TThostFtdcCurrencyCodeType", "CurrencyCode", &(m_ThostFtdcTransferQryBankReqField.CurrencyCode));

	RegField("CThostFtdcTransferQryBankRspField","响应代码","TThostFtdcRetCodeType", "RetCode", &(m_ThostFtdcTransferQryBankRspField.RetCode));
	RegField("CThostFtdcTransferQryBankRspField","响应信息","TThostFtdcRetInfoType", "RetInfo", &(m_ThostFtdcTransferQryBankRspField.RetInfo));
	RegField("CThostFtdcTransferQryBankRspField","资金账户","TThostFtdcAccountIDType", "FutureAccount", &(m_ThostFtdcTransferQryBankRspField.FutureAccount));
	RegField("CThostFtdcTransferQryBankRspField","银行余额","TThostFtdcMoneyType", "TradeAmt", &(m_ThostFtdcTransferQryBankRspField.TradeAmt));
	RegField("CThostFtdcTransferQryBankRspField","银行可用余额","TThostFtdcMoneyType", "UseAmt", &(m_ThostFtdcTransferQryBankRspField.UseAmt));
	RegField("CThostFtdcTransferQryBankRspField","银行可取余额","TThostFtdcMoneyType", "FetchAmt", &(m_ThostFtdcTransferQryBankRspField.FetchAmt));
	RegField("CThostFtdcTransferQryBankRspField","币种","TThostFtdcCurrencyCodeType", "CurrencyCode", &(m_ThostFtdcTransferQryBankRspField.CurrencyCode));

	RegField("CThostFtdcTransferQryDetailReqField","期货资金账户","TThostFtdcAccountIDType", "FutureAccount", &(m_ThostFtdcTransferQryDetailReqField.FutureAccount));

	RegField("CThostFtdcTransferQryDetailRspField","交易日期","TThostFtdcDateType", "TradeDate", &(m_ThostFtdcTransferQryDetailRspField.TradeDate));
	RegField("CThostFtdcTransferQryDetailRspField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcTransferQryDetailRspField.TradeTime));
	RegField("CThostFtdcTransferQryDetailRspField","交易代码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcTransferQryDetailRspField.TradeCode));
	RegField("CThostFtdcTransferQryDetailRspField","期货流水号","TThostFtdcTradeSerialNoType", "FutureSerial", &(m_ThostFtdcTransferQryDetailRspField.FutureSerial));
	RegField("CThostFtdcTransferQryDetailRspField","期货公司代码","TThostFtdcFutureIDType", "FutureID", &(m_ThostFtdcTransferQryDetailRspField.FutureID));
	RegField("CThostFtdcTransferQryDetailRspField","资金帐号","TThostFtdcFutureAccountType", "FutureAccount", &(m_ThostFtdcTransferQryDetailRspField.FutureAccount));
	RegField("CThostFtdcTransferQryDetailRspField","银行流水号","TThostFtdcTradeSerialNoType", "BankSerial", &(m_ThostFtdcTransferQryDetailRspField.BankSerial));
	RegField("CThostFtdcTransferQryDetailRspField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcTransferQryDetailRspField.BankID));
	RegField("CThostFtdcTransferQryDetailRspField","银行分中心代码","TThostFtdcBankBrchIDType", "BankBrchID", &(m_ThostFtdcTransferQryDetailRspField.BankBrchID));
	RegField("CThostFtdcTransferQryDetailRspField","银行账号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcTransferQryDetailRspField.BankAccount));
	RegField("CThostFtdcTransferQryDetailRspField","证件号码","TThostFtdcCertCodeType", "CertCode", &(m_ThostFtdcTransferQryDetailRspField.CertCode));
	RegField("CThostFtdcTransferQryDetailRspField","货币代码","TThostFtdcCurrencyCodeType", "CurrencyCode", &(m_ThostFtdcTransferQryDetailRspField.CurrencyCode));
	RegField("CThostFtdcTransferQryDetailRspField","发生金额","TThostFtdcMoneyType", "TxAmount", &(m_ThostFtdcTransferQryDetailRspField.TxAmount));
	RegField("CThostFtdcTransferQryDetailRspField","有效标志","TThostFtdcTransferValidFlagType", "Flag", &(m_ThostFtdcTransferQryDetailRspField.Flag));

	RegField("CThostFtdcRspInfoField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcRspInfoField.ErrorID));
	RegField("CThostFtdcRspInfoField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcRspInfoField.ErrorMsg));

	RegField("CThostFtdcExchangeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeField.ExchangeID));
	RegField("CThostFtdcExchangeField","交易所名称","TThostFtdcExchangeNameType", "ExchangeName", &(m_ThostFtdcExchangeField.ExchangeName));
	RegField("CThostFtdcExchangeField","交易所属性","TThostFtdcExchangePropertyType", "ExchangeProperty", &(m_ThostFtdcExchangeField.ExchangeProperty));

	RegField("CThostFtdcProductField","产品代码","TThostFtdcInstrumentIDType", "ProductID", &(m_ThostFtdcProductField.ProductID));
	RegField("CThostFtdcProductField","产品名称","TThostFtdcProductNameType", "ProductName", &(m_ThostFtdcProductField.ProductName));
	RegField("CThostFtdcProductField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcProductField.ExchangeID));
	RegField("CThostFtdcProductField","产品类型","TThostFtdcProductClassType", "ProductClass", &(m_ThostFtdcProductField.ProductClass));
	RegField("CThostFtdcProductField","合约数量乘数","TThostFtdcVolumeMultipleType", "VolumeMultiple", &(m_ThostFtdcProductField.VolumeMultiple));
	RegField("CThostFtdcProductField","最小变动价位","TThostFtdcPriceType", "PriceTick", &(m_ThostFtdcProductField.PriceTick));
	RegField("CThostFtdcProductField","市价单最大下单量","TThostFtdcVolumeType", "MaxMarketOrderVolume", &(m_ThostFtdcProductField.MaxMarketOrderVolume));
	RegField("CThostFtdcProductField","市价单最小下单量","TThostFtdcVolumeType", "MinMarketOrderVolume", &(m_ThostFtdcProductField.MinMarketOrderVolume));
	RegField("CThostFtdcProductField","限价单最大下单量","TThostFtdcVolumeType", "MaxLimitOrderVolume", &(m_ThostFtdcProductField.MaxLimitOrderVolume));
	RegField("CThostFtdcProductField","限价单最小下单量","TThostFtdcVolumeType", "MinLimitOrderVolume", &(m_ThostFtdcProductField.MinLimitOrderVolume));
	RegField("CThostFtdcProductField","持仓类型","TThostFtdcPositionTypeType", "PositionType", &(m_ThostFtdcProductField.PositionType));
	RegField("CThostFtdcProductField","持仓日期类型","TThostFtdcPositionDateTypeType", "PositionDateType", &(m_ThostFtdcProductField.PositionDateType));
	RegField("CThostFtdcProductField","平仓处理类型","TThostFtdcCloseDealTypeType", "CloseDealType", &(m_ThostFtdcProductField.CloseDealType));
	RegField("CThostFtdcProductField","交易币种类型","TThostFtdcCurrencyIDType", "TradeCurrencyID", &(m_ThostFtdcProductField.TradeCurrencyID));
	RegField("CThostFtdcProductField","质押资金可用范围","TThostFtdcMortgageFundUseRangeType", "MortgageFundUseRange", &(m_ThostFtdcProductField.MortgageFundUseRange));
	RegField("CThostFtdcProductField","交易所产品代码","TThostFtdcInstrumentIDType", "ExchangeProductID", &(m_ThostFtdcProductField.ExchangeProductID));
	RegField("CThostFtdcProductField","合约基础商品乘数","TThostFtdcUnderlyingMultipleType", "UnderlyingMultiple", &(m_ThostFtdcProductField.UnderlyingMultiple));

	RegField("CThostFtdcInstrumentField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInstrumentField.InstrumentID));
	RegField("CThostFtdcInstrumentField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcInstrumentField.ExchangeID));
	RegField("CThostFtdcInstrumentField","合约名称","TThostFtdcInstrumentNameType", "InstrumentName", &(m_ThostFtdcInstrumentField.InstrumentName));
	RegField("CThostFtdcInstrumentField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcInstrumentField.ExchangeInstID));
	RegField("CThostFtdcInstrumentField","产品代码","TThostFtdcInstrumentIDType", "ProductID", &(m_ThostFtdcInstrumentField.ProductID));
	RegField("CThostFtdcInstrumentField","产品类型","TThostFtdcProductClassType", "ProductClass", &(m_ThostFtdcInstrumentField.ProductClass));
	RegField("CThostFtdcInstrumentField","交割年份","TThostFtdcYearType", "DeliveryYear", &(m_ThostFtdcInstrumentField.DeliveryYear));
	RegField("CThostFtdcInstrumentField","交割月","TThostFtdcMonthType", "DeliveryMonth", &(m_ThostFtdcInstrumentField.DeliveryMonth));
	RegField("CThostFtdcInstrumentField","市价单最大下单量","TThostFtdcVolumeType", "MaxMarketOrderVolume", &(m_ThostFtdcInstrumentField.MaxMarketOrderVolume));
	RegField("CThostFtdcInstrumentField","市价单最小下单量","TThostFtdcVolumeType", "MinMarketOrderVolume", &(m_ThostFtdcInstrumentField.MinMarketOrderVolume));
	RegField("CThostFtdcInstrumentField","限价单最大下单量","TThostFtdcVolumeType", "MaxLimitOrderVolume", &(m_ThostFtdcInstrumentField.MaxLimitOrderVolume));
	RegField("CThostFtdcInstrumentField","限价单最小下单量","TThostFtdcVolumeType", "MinLimitOrderVolume", &(m_ThostFtdcInstrumentField.MinLimitOrderVolume));
	RegField("CThostFtdcInstrumentField","合约数量乘数","TThostFtdcVolumeMultipleType", "VolumeMultiple", &(m_ThostFtdcInstrumentField.VolumeMultiple));
	RegField("CThostFtdcInstrumentField","最小变动价位","TThostFtdcPriceType", "PriceTick", &(m_ThostFtdcInstrumentField.PriceTick));
	RegField("CThostFtdcInstrumentField","创建日","TThostFtdcDateType", "CreateDate", &(m_ThostFtdcInstrumentField.CreateDate));
	RegField("CThostFtdcInstrumentField","上市日","TThostFtdcDateType", "OpenDate", &(m_ThostFtdcInstrumentField.OpenDate));
	RegField("CThostFtdcInstrumentField","到期日","TThostFtdcDateType", "ExpireDate", &(m_ThostFtdcInstrumentField.ExpireDate));
	RegField("CThostFtdcInstrumentField","开始交割日","TThostFtdcDateType", "StartDelivDate", &(m_ThostFtdcInstrumentField.StartDelivDate));
	RegField("CThostFtdcInstrumentField","结束交割日","TThostFtdcDateType", "EndDelivDate", &(m_ThostFtdcInstrumentField.EndDelivDate));
	RegField("CThostFtdcInstrumentField","合约生命周期状态","TThostFtdcInstLifePhaseType", "InstLifePhase", &(m_ThostFtdcInstrumentField.InstLifePhase));
	RegField("CThostFtdcInstrumentField","当前是否交易","TThostFtdcBoolType", "IsTrading", &(m_ThostFtdcInstrumentField.IsTrading));
	RegField("CThostFtdcInstrumentField","持仓类型","TThostFtdcPositionTypeType", "PositionType", &(m_ThostFtdcInstrumentField.PositionType));
	RegField("CThostFtdcInstrumentField","持仓日期类型","TThostFtdcPositionDateTypeType", "PositionDateType", &(m_ThostFtdcInstrumentField.PositionDateType));
	RegField("CThostFtdcInstrumentField","多头保证金率","TThostFtdcRatioType", "LongMarginRatio", &(m_ThostFtdcInstrumentField.LongMarginRatio));
	RegField("CThostFtdcInstrumentField","空头保证金率","TThostFtdcRatioType", "ShortMarginRatio", &(m_ThostFtdcInstrumentField.ShortMarginRatio));
	RegField("CThostFtdcInstrumentField","是否使用大额单边保证金算法","TThostFtdcMaxMarginSideAlgorithmType", "MaxMarginSideAlgorithm", &(m_ThostFtdcInstrumentField.MaxMarginSideAlgorithm));
	RegField("CThostFtdcInstrumentField","基础商品代码","TThostFtdcInstrumentIDType", "UnderlyingInstrID", &(m_ThostFtdcInstrumentField.UnderlyingInstrID));
	RegField("CThostFtdcInstrumentField","执行价","TThostFtdcPriceType", "StrikePrice", &(m_ThostFtdcInstrumentField.StrikePrice));
	RegField("CThostFtdcInstrumentField","期权类型","TThostFtdcOptionsTypeType", "OptionsType", &(m_ThostFtdcInstrumentField.OptionsType));
	RegField("CThostFtdcInstrumentField","合约基础商品乘数","TThostFtdcUnderlyingMultipleType", "UnderlyingMultiple", &(m_ThostFtdcInstrumentField.UnderlyingMultiple));
	RegField("CThostFtdcInstrumentField","组合类型","TThostFtdcCombinationTypeType", "CombinationType", &(m_ThostFtdcInstrumentField.CombinationType));

	RegField("CThostFtdcBrokerField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerField.BrokerID));
	RegField("CThostFtdcBrokerField","经纪公司简称","TThostFtdcBrokerAbbrType", "BrokerAbbr", &(m_ThostFtdcBrokerField.BrokerAbbr));
	RegField("CThostFtdcBrokerField","经纪公司名称","TThostFtdcBrokerNameType", "BrokerName", &(m_ThostFtdcBrokerField.BrokerName));
	RegField("CThostFtdcBrokerField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcBrokerField.IsActive));

	RegField("CThostFtdcTraderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcTraderField.ExchangeID));
	RegField("CThostFtdcTraderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcTraderField.TraderID));
	RegField("CThostFtdcTraderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcTraderField.ParticipantID));
	RegField("CThostFtdcTraderField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcTraderField.Password));
	RegField("CThostFtdcTraderField","安装数量","TThostFtdcInstallCountType", "InstallCount", &(m_ThostFtdcTraderField.InstallCount));
	RegField("CThostFtdcTraderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTraderField.BrokerID));

	RegField("CThostFtdcInvestorField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInvestorField.InvestorID));
	RegField("CThostFtdcInvestorField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorField.BrokerID));
	RegField("CThostFtdcInvestorField","投资者分组代码","TThostFtdcInvestorIDType", "InvestorGroupID", &(m_ThostFtdcInvestorField.InvestorGroupID));
	RegField("CThostFtdcInvestorField","投资者名称","TThostFtdcPartyNameType", "InvestorName", &(m_ThostFtdcInvestorField.InvestorName));
	RegField("CThostFtdcInvestorField","证件类型","TThostFtdcIdCardTypeType", "IdentifiedCardType", &(m_ThostFtdcInvestorField.IdentifiedCardType));
	RegField("CThostFtdcInvestorField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcInvestorField.IdentifiedCardNo));
	RegField("CThostFtdcInvestorField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcInvestorField.IsActive));
	RegField("CThostFtdcInvestorField","联系电话","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcInvestorField.Telephone));
	RegField("CThostFtdcInvestorField","通讯地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcInvestorField.Address));
	RegField("CThostFtdcInvestorField","开户日期","TThostFtdcDateType", "OpenDate", &(m_ThostFtdcInvestorField.OpenDate));
	RegField("CThostFtdcInvestorField","手机","TThostFtdcMobileType", "Mobile", &(m_ThostFtdcInvestorField.Mobile));
	RegField("CThostFtdcInvestorField","手续费率模板代码","TThostFtdcInvestorIDType", "CommModelID", &(m_ThostFtdcInvestorField.CommModelID));
	RegField("CThostFtdcInvestorField","保证金率模板代码","TThostFtdcInvestorIDType", "MarginModelID", &(m_ThostFtdcInvestorField.MarginModelID));

	RegField("CThostFtdcTradingCodeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcTradingCodeField.InvestorID));
	RegField("CThostFtdcTradingCodeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingCodeField.BrokerID));
	RegField("CThostFtdcTradingCodeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcTradingCodeField.ExchangeID));
	RegField("CThostFtdcTradingCodeField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcTradingCodeField.ClientID));
	RegField("CThostFtdcTradingCodeField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcTradingCodeField.IsActive));
	RegField("CThostFtdcTradingCodeField","交易编码类型","TThostFtdcClientIDTypeType", "ClientIDType", &(m_ThostFtdcTradingCodeField.ClientIDType));

	RegField("CThostFtdcPartBrokerField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcPartBrokerField.BrokerID));
	RegField("CThostFtdcPartBrokerField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcPartBrokerField.ExchangeID));
	RegField("CThostFtdcPartBrokerField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcPartBrokerField.ParticipantID));
	RegField("CThostFtdcPartBrokerField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcPartBrokerField.IsActive));

	RegField("CThostFtdcSuperUserField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcSuperUserField.UserID));
	RegField("CThostFtdcSuperUserField","用户名称","TThostFtdcUserNameType", "UserName", &(m_ThostFtdcSuperUserField.UserName));
	RegField("CThostFtdcSuperUserField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcSuperUserField.Password));
	RegField("CThostFtdcSuperUserField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcSuperUserField.IsActive));

	RegField("CThostFtdcSuperUserFunctionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcSuperUserFunctionField.UserID));
	RegField("CThostFtdcSuperUserFunctionField","功能代码","TThostFtdcFunctionCodeType", "FunctionCode", &(m_ThostFtdcSuperUserFunctionField.FunctionCode));

	RegField("CThostFtdcInvestorGroupField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorGroupField.BrokerID));
	RegField("CThostFtdcInvestorGroupField","投资者分组代码","TThostFtdcInvestorIDType", "InvestorGroupID", &(m_ThostFtdcInvestorGroupField.InvestorGroupID));
	RegField("CThostFtdcInvestorGroupField","投资者分组名称","TThostFtdcInvestorGroupNameType", "InvestorGroupName", &(m_ThostFtdcInvestorGroupField.InvestorGroupName));

	RegField("CThostFtdcTradingAccountField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingAccountField.BrokerID));
	RegField("CThostFtdcTradingAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcTradingAccountField.AccountID));
	RegField("CThostFtdcTradingAccountField","上次质押金额","TThostFtdcMoneyType", "PreMortgage", &(m_ThostFtdcTradingAccountField.PreMortgage));
	RegField("CThostFtdcTradingAccountField","上次信用额度","TThostFtdcMoneyType", "PreCredit", &(m_ThostFtdcTradingAccountField.PreCredit));
	RegField("CThostFtdcTradingAccountField","上次存款额","TThostFtdcMoneyType", "PreDeposit", &(m_ThostFtdcTradingAccountField.PreDeposit));
	RegField("CThostFtdcTradingAccountField","上次结算准备金","TThostFtdcMoneyType", "PreBalance", &(m_ThostFtdcTradingAccountField.PreBalance));
	RegField("CThostFtdcTradingAccountField","上次占用的保证金","TThostFtdcMoneyType", "PreMargin", &(m_ThostFtdcTradingAccountField.PreMargin));
	RegField("CThostFtdcTradingAccountField","利息基数","TThostFtdcMoneyType", "InterestBase", &(m_ThostFtdcTradingAccountField.InterestBase));
	RegField("CThostFtdcTradingAccountField","利息收入","TThostFtdcMoneyType", "Interest", &(m_ThostFtdcTradingAccountField.Interest));
	RegField("CThostFtdcTradingAccountField","入金金额","TThostFtdcMoneyType", "Deposit", &(m_ThostFtdcTradingAccountField.Deposit));
	RegField("CThostFtdcTradingAccountField","出金金额","TThostFtdcMoneyType", "Withdraw", &(m_ThostFtdcTradingAccountField.Withdraw));
	RegField("CThostFtdcTradingAccountField","冻结的保证金","TThostFtdcMoneyType", "FrozenMargin", &(m_ThostFtdcTradingAccountField.FrozenMargin));
	RegField("CThostFtdcTradingAccountField","冻结的资金","TThostFtdcMoneyType", "FrozenCash", &(m_ThostFtdcTradingAccountField.FrozenCash));
	RegField("CThostFtdcTradingAccountField","冻结的手续费","TThostFtdcMoneyType", "FrozenCommission", &(m_ThostFtdcTradingAccountField.FrozenCommission));
	RegField("CThostFtdcTradingAccountField","当前保证金总额","TThostFtdcMoneyType", "CurrMargin", &(m_ThostFtdcTradingAccountField.CurrMargin));
	RegField("CThostFtdcTradingAccountField","资金差额","TThostFtdcMoneyType", "CashIn", &(m_ThostFtdcTradingAccountField.CashIn));
	RegField("CThostFtdcTradingAccountField","手续费","TThostFtdcMoneyType", "Commission", &(m_ThostFtdcTradingAccountField.Commission));
	RegField("CThostFtdcTradingAccountField","平仓盈亏","TThostFtdcMoneyType", "CloseProfit", &(m_ThostFtdcTradingAccountField.CloseProfit));
	RegField("CThostFtdcTradingAccountField","持仓盈亏","TThostFtdcMoneyType", "PositionProfit", &(m_ThostFtdcTradingAccountField.PositionProfit));
	RegField("CThostFtdcTradingAccountField","期货结算准备金","TThostFtdcMoneyType", "Balance", &(m_ThostFtdcTradingAccountField.Balance));
	RegField("CThostFtdcTradingAccountField","可用资金","TThostFtdcMoneyType", "Available", &(m_ThostFtdcTradingAccountField.Available));
	RegField("CThostFtdcTradingAccountField","可取资金","TThostFtdcMoneyType", "WithdrawQuota", &(m_ThostFtdcTradingAccountField.WithdrawQuota));
	RegField("CThostFtdcTradingAccountField","基本准备金","TThostFtdcMoneyType", "Reserve", &(m_ThostFtdcTradingAccountField.Reserve));
	RegField("CThostFtdcTradingAccountField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcTradingAccountField.TradingDay));
	RegField("CThostFtdcTradingAccountField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcTradingAccountField.SettlementID));
	RegField("CThostFtdcTradingAccountField","信用额度","TThostFtdcMoneyType", "Credit", &(m_ThostFtdcTradingAccountField.Credit));
	RegField("CThostFtdcTradingAccountField","质押金额","TThostFtdcMoneyType", "Mortgage", &(m_ThostFtdcTradingAccountField.Mortgage));
	RegField("CThostFtdcTradingAccountField","交易所保证金","TThostFtdcMoneyType", "ExchangeMargin", &(m_ThostFtdcTradingAccountField.ExchangeMargin));
	RegField("CThostFtdcTradingAccountField","投资者交割保证金","TThostFtdcMoneyType", "DeliveryMargin", &(m_ThostFtdcTradingAccountField.DeliveryMargin));
	RegField("CThostFtdcTradingAccountField","交易所交割保证金","TThostFtdcMoneyType", "ExchangeDeliveryMargin", &(m_ThostFtdcTradingAccountField.ExchangeDeliveryMargin));
	RegField("CThostFtdcTradingAccountField","保底期货结算准备金","TThostFtdcMoneyType", "ReserveBalance", &(m_ThostFtdcTradingAccountField.ReserveBalance));
	RegField("CThostFtdcTradingAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcTradingAccountField.CurrencyID));
	RegField("CThostFtdcTradingAccountField","上次货币质入金额","TThostFtdcMoneyType", "PreFundMortgageIn", &(m_ThostFtdcTradingAccountField.PreFundMortgageIn));
	RegField("CThostFtdcTradingAccountField","上次货币质出金额","TThostFtdcMoneyType", "PreFundMortgageOut", &(m_ThostFtdcTradingAccountField.PreFundMortgageOut));
	RegField("CThostFtdcTradingAccountField","货币质入金额","TThostFtdcMoneyType", "FundMortgageIn", &(m_ThostFtdcTradingAccountField.FundMortgageIn));
	RegField("CThostFtdcTradingAccountField","货币质出金额","TThostFtdcMoneyType", "FundMortgageOut", &(m_ThostFtdcTradingAccountField.FundMortgageOut));
	RegField("CThostFtdcTradingAccountField","货币质押余额","TThostFtdcMoneyType", "FundMortgageAvailable", &(m_ThostFtdcTradingAccountField.FundMortgageAvailable));
	RegField("CThostFtdcTradingAccountField","可质押货币金额","TThostFtdcMoneyType", "MortgageableFund", &(m_ThostFtdcTradingAccountField.MortgageableFund));
	RegField("CThostFtdcTradingAccountField","特殊产品占用保证金","TThostFtdcMoneyType", "SpecProductMargin", &(m_ThostFtdcTradingAccountField.SpecProductMargin));
	RegField("CThostFtdcTradingAccountField","特殊产品冻结保证金","TThostFtdcMoneyType", "SpecProductFrozenMargin", &(m_ThostFtdcTradingAccountField.SpecProductFrozenMargin));
	RegField("CThostFtdcTradingAccountField","特殊产品手续费","TThostFtdcMoneyType", "SpecProductCommission", &(m_ThostFtdcTradingAccountField.SpecProductCommission));
	RegField("CThostFtdcTradingAccountField","特殊产品冻结手续费","TThostFtdcMoneyType", "SpecProductFrozenCommission", &(m_ThostFtdcTradingAccountField.SpecProductFrozenCommission));
	RegField("CThostFtdcTradingAccountField","特殊产品持仓盈亏","TThostFtdcMoneyType", "SpecProductPositionProfit", &(m_ThostFtdcTradingAccountField.SpecProductPositionProfit));
	RegField("CThostFtdcTradingAccountField","特殊产品平仓盈亏","TThostFtdcMoneyType", "SpecProductCloseProfit", &(m_ThostFtdcTradingAccountField.SpecProductCloseProfit));
	RegField("CThostFtdcTradingAccountField","根据持仓盈亏算法计算的特殊产品持仓盈亏","TThostFtdcMoneyType", "SpecProductPositionProfitByAlg", &(m_ThostFtdcTradingAccountField.SpecProductPositionProfitByAlg));
	RegField("CThostFtdcTradingAccountField","特殊产品交易所保证金","TThostFtdcMoneyType", "SpecProductExchangeMargin", &(m_ThostFtdcTradingAccountField.SpecProductExchangeMargin));
	RegField("CThostFtdcTradingAccountField","期权平仓盈亏","TThostFtdcMoneyType", "OptionCloseProfit", &(m_ThostFtdcTradingAccountField.OptionCloseProfit));
	RegField("CThostFtdcTradingAccountField","期权市值","TThostFtdcMoneyType", "OptionValue", &(m_ThostFtdcTradingAccountField.OptionValue));

	RegField("CThostFtdcInvestorPositionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInvestorPositionField.InstrumentID));
	RegField("CThostFtdcInvestorPositionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorPositionField.BrokerID));
	RegField("CThostFtdcInvestorPositionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInvestorPositionField.InvestorID));
	RegField("CThostFtdcInvestorPositionField","持仓多空方向","TThostFtdcPosiDirectionType", "PosiDirection", &(m_ThostFtdcInvestorPositionField.PosiDirection));
	RegField("CThostFtdcInvestorPositionField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcInvestorPositionField.HedgeFlag));
	RegField("CThostFtdcInvestorPositionField","持仓日期","TThostFtdcPositionDateType", "PositionDate", &(m_ThostFtdcInvestorPositionField.PositionDate));
	RegField("CThostFtdcInvestorPositionField","上日持仓","TThostFtdcVolumeType", "YdPosition", &(m_ThostFtdcInvestorPositionField.YdPosition));
	RegField("CThostFtdcInvestorPositionField","今日持仓","TThostFtdcVolumeType", "Position", &(m_ThostFtdcInvestorPositionField.Position));
	RegField("CThostFtdcInvestorPositionField","多头冻结","TThostFtdcVolumeType", "LongFrozen", &(m_ThostFtdcInvestorPositionField.LongFrozen));
	RegField("CThostFtdcInvestorPositionField","空头冻结","TThostFtdcVolumeType", "ShortFrozen", &(m_ThostFtdcInvestorPositionField.ShortFrozen));
	RegField("CThostFtdcInvestorPositionField","开仓冻结金额","TThostFtdcMoneyType", "LongFrozenAmount", &(m_ThostFtdcInvestorPositionField.LongFrozenAmount));
	RegField("CThostFtdcInvestorPositionField","开仓冻结金额","TThostFtdcMoneyType", "ShortFrozenAmount", &(m_ThostFtdcInvestorPositionField.ShortFrozenAmount));
	RegField("CThostFtdcInvestorPositionField","开仓量","TThostFtdcVolumeType", "OpenVolume", &(m_ThostFtdcInvestorPositionField.OpenVolume));
	RegField("CThostFtdcInvestorPositionField","平仓量","TThostFtdcVolumeType", "CloseVolume", &(m_ThostFtdcInvestorPositionField.CloseVolume));
	RegField("CThostFtdcInvestorPositionField","开仓金额","TThostFtdcMoneyType", "OpenAmount", &(m_ThostFtdcInvestorPositionField.OpenAmount));
	RegField("CThostFtdcInvestorPositionField","平仓金额","TThostFtdcMoneyType", "CloseAmount", &(m_ThostFtdcInvestorPositionField.CloseAmount));
	RegField("CThostFtdcInvestorPositionField","持仓成本","TThostFtdcMoneyType", "PositionCost", &(m_ThostFtdcInvestorPositionField.PositionCost));
	RegField("CThostFtdcInvestorPositionField","上次占用的保证金","TThostFtdcMoneyType", "PreMargin", &(m_ThostFtdcInvestorPositionField.PreMargin));
	RegField("CThostFtdcInvestorPositionField","占用的保证金","TThostFtdcMoneyType", "UseMargin", &(m_ThostFtdcInvestorPositionField.UseMargin));
	RegField("CThostFtdcInvestorPositionField","冻结的保证金","TThostFtdcMoneyType", "FrozenMargin", &(m_ThostFtdcInvestorPositionField.FrozenMargin));
	RegField("CThostFtdcInvestorPositionField","冻结的资金","TThostFtdcMoneyType", "FrozenCash", &(m_ThostFtdcInvestorPositionField.FrozenCash));
	RegField("CThostFtdcInvestorPositionField","冻结的手续费","TThostFtdcMoneyType", "FrozenCommission", &(m_ThostFtdcInvestorPositionField.FrozenCommission));
	RegField("CThostFtdcInvestorPositionField","资金差额","TThostFtdcMoneyType", "CashIn", &(m_ThostFtdcInvestorPositionField.CashIn));
	RegField("CThostFtdcInvestorPositionField","手续费","TThostFtdcMoneyType", "Commission", &(m_ThostFtdcInvestorPositionField.Commission));
	RegField("CThostFtdcInvestorPositionField","平仓盈亏","TThostFtdcMoneyType", "CloseProfit", &(m_ThostFtdcInvestorPositionField.CloseProfit));
	RegField("CThostFtdcInvestorPositionField","持仓盈亏","TThostFtdcMoneyType", "PositionProfit", &(m_ThostFtdcInvestorPositionField.PositionProfit));
	RegField("CThostFtdcInvestorPositionField","上次结算价","TThostFtdcPriceType", "PreSettlementPrice", &(m_ThostFtdcInvestorPositionField.PreSettlementPrice));
	RegField("CThostFtdcInvestorPositionField","本次结算价","TThostFtdcPriceType", "SettlementPrice", &(m_ThostFtdcInvestorPositionField.SettlementPrice));
	RegField("CThostFtdcInvestorPositionField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcInvestorPositionField.TradingDay));
	RegField("CThostFtdcInvestorPositionField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcInvestorPositionField.SettlementID));
	RegField("CThostFtdcInvestorPositionField","开仓成本","TThostFtdcMoneyType", "OpenCost", &(m_ThostFtdcInvestorPositionField.OpenCost));
	RegField("CThostFtdcInvestorPositionField","交易所保证金","TThostFtdcMoneyType", "ExchangeMargin", &(m_ThostFtdcInvestorPositionField.ExchangeMargin));
	RegField("CThostFtdcInvestorPositionField","组合成交形成的持仓","TThostFtdcVolumeType", "CombPosition", &(m_ThostFtdcInvestorPositionField.CombPosition));
	RegField("CThostFtdcInvestorPositionField","组合多头冻结","TThostFtdcVolumeType", "CombLongFrozen", &(m_ThostFtdcInvestorPositionField.CombLongFrozen));
	RegField("CThostFtdcInvestorPositionField","组合空头冻结","TThostFtdcVolumeType", "CombShortFrozen", &(m_ThostFtdcInvestorPositionField.CombShortFrozen));
	RegField("CThostFtdcInvestorPositionField","逐日盯市平仓盈亏","TThostFtdcMoneyType", "CloseProfitByDate", &(m_ThostFtdcInvestorPositionField.CloseProfitByDate));
	RegField("CThostFtdcInvestorPositionField","逐笔对冲平仓盈亏","TThostFtdcMoneyType", "CloseProfitByTrade", &(m_ThostFtdcInvestorPositionField.CloseProfitByTrade));
	RegField("CThostFtdcInvestorPositionField","今日持仓","TThostFtdcVolumeType", "TodayPosition", &(m_ThostFtdcInvestorPositionField.TodayPosition));
	RegField("CThostFtdcInvestorPositionField","保证金率","TThostFtdcRatioType", "MarginRateByMoney", &(m_ThostFtdcInvestorPositionField.MarginRateByMoney));
	RegField("CThostFtdcInvestorPositionField","保证金率","TThostFtdcRatioType", "MarginRateByVolume", &(m_ThostFtdcInvestorPositionField.MarginRateByVolume));
	RegField("CThostFtdcInvestorPositionField","执行冻结","TThostFtdcVolumeType", "StrikeFrozen", &(m_ThostFtdcInvestorPositionField.StrikeFrozen));
	RegField("CThostFtdcInvestorPositionField","执行冻结金额","TThostFtdcMoneyType", "StrikeFrozenAmount", &(m_ThostFtdcInvestorPositionField.StrikeFrozenAmount));
	RegField("CThostFtdcInvestorPositionField","放弃执行冻结","TThostFtdcVolumeType", "AbandonFrozen", &(m_ThostFtdcInvestorPositionField.AbandonFrozen));
	RegField("CThostFtdcInvestorPositionField","期权市值","TThostFtdcMoneyType", "OptionValue", &(m_ThostFtdcInvestorPositionField.OptionValue));

	RegField("CThostFtdcInstrumentMarginRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInstrumentMarginRateField.InstrumentID));
	RegField("CThostFtdcInstrumentMarginRateField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcInstrumentMarginRateField.InvestorRange));
	RegField("CThostFtdcInstrumentMarginRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInstrumentMarginRateField.BrokerID));
	RegField("CThostFtdcInstrumentMarginRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInstrumentMarginRateField.InvestorID));
	RegField("CThostFtdcInstrumentMarginRateField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcInstrumentMarginRateField.HedgeFlag));
	RegField("CThostFtdcInstrumentMarginRateField","多头保证金率","TThostFtdcRatioType", "LongMarginRatioByMoney", &(m_ThostFtdcInstrumentMarginRateField.LongMarginRatioByMoney));
	RegField("CThostFtdcInstrumentMarginRateField","多头保证金费","TThostFtdcMoneyType", "LongMarginRatioByVolume", &(m_ThostFtdcInstrumentMarginRateField.LongMarginRatioByVolume));
	RegField("CThostFtdcInstrumentMarginRateField","空头保证金率","TThostFtdcRatioType", "ShortMarginRatioByMoney", &(m_ThostFtdcInstrumentMarginRateField.ShortMarginRatioByMoney));
	RegField("CThostFtdcInstrumentMarginRateField","空头保证金费","TThostFtdcMoneyType", "ShortMarginRatioByVolume", &(m_ThostFtdcInstrumentMarginRateField.ShortMarginRatioByVolume));
	RegField("CThostFtdcInstrumentMarginRateField","是否相对交易所收取","TThostFtdcBoolType", "IsRelative", &(m_ThostFtdcInstrumentMarginRateField.IsRelative));

	RegField("CThostFtdcInstrumentCommissionRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInstrumentCommissionRateField.InstrumentID));
	RegField("CThostFtdcInstrumentCommissionRateField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcInstrumentCommissionRateField.InvestorRange));
	RegField("CThostFtdcInstrumentCommissionRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInstrumentCommissionRateField.BrokerID));
	RegField("CThostFtdcInstrumentCommissionRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInstrumentCommissionRateField.InvestorID));
	RegField("CThostFtdcInstrumentCommissionRateField","开仓手续费率","TThostFtdcRatioType", "OpenRatioByMoney", &(m_ThostFtdcInstrumentCommissionRateField.OpenRatioByMoney));
	RegField("CThostFtdcInstrumentCommissionRateField","开仓手续费","TThostFtdcRatioType", "OpenRatioByVolume", &(m_ThostFtdcInstrumentCommissionRateField.OpenRatioByVolume));
	RegField("CThostFtdcInstrumentCommissionRateField","平仓手续费率","TThostFtdcRatioType", "CloseRatioByMoney", &(m_ThostFtdcInstrumentCommissionRateField.CloseRatioByMoney));
	RegField("CThostFtdcInstrumentCommissionRateField","平仓手续费","TThostFtdcRatioType", "CloseRatioByVolume", &(m_ThostFtdcInstrumentCommissionRateField.CloseRatioByVolume));
	RegField("CThostFtdcInstrumentCommissionRateField","平今手续费率","TThostFtdcRatioType", "CloseTodayRatioByMoney", &(m_ThostFtdcInstrumentCommissionRateField.CloseTodayRatioByMoney));
	RegField("CThostFtdcInstrumentCommissionRateField","平今手续费","TThostFtdcRatioType", "CloseTodayRatioByVolume", &(m_ThostFtdcInstrumentCommissionRateField.CloseTodayRatioByVolume));

	RegField("CThostFtdcDepthMarketDataField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcDepthMarketDataField.TradingDay));
	RegField("CThostFtdcDepthMarketDataField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcDepthMarketDataField.InstrumentID));
	RegField("CThostFtdcDepthMarketDataField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcDepthMarketDataField.ExchangeID));
	RegField("CThostFtdcDepthMarketDataField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcDepthMarketDataField.ExchangeInstID));
	RegField("CThostFtdcDepthMarketDataField","最新价","TThostFtdcPriceType", "LastPrice", &(m_ThostFtdcDepthMarketDataField.LastPrice));
	RegField("CThostFtdcDepthMarketDataField","上次结算价","TThostFtdcPriceType", "PreSettlementPrice", &(m_ThostFtdcDepthMarketDataField.PreSettlementPrice));
	RegField("CThostFtdcDepthMarketDataField","昨收盘","TThostFtdcPriceType", "PreClosePrice", &(m_ThostFtdcDepthMarketDataField.PreClosePrice));
	RegField("CThostFtdcDepthMarketDataField","昨持仓量","TThostFtdcLargeVolumeType", "PreOpenInterest", &(m_ThostFtdcDepthMarketDataField.PreOpenInterest));
	RegField("CThostFtdcDepthMarketDataField","今开盘","TThostFtdcPriceType", "OpenPrice", &(m_ThostFtdcDepthMarketDataField.OpenPrice));
	RegField("CThostFtdcDepthMarketDataField","最高价","TThostFtdcPriceType", "HighestPrice", &(m_ThostFtdcDepthMarketDataField.HighestPrice));
	RegField("CThostFtdcDepthMarketDataField","最低价","TThostFtdcPriceType", "LowestPrice", &(m_ThostFtdcDepthMarketDataField.LowestPrice));
	RegField("CThostFtdcDepthMarketDataField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcDepthMarketDataField.Volume));
	RegField("CThostFtdcDepthMarketDataField","成交金额","TThostFtdcMoneyType", "Turnover", &(m_ThostFtdcDepthMarketDataField.Turnover));
	RegField("CThostFtdcDepthMarketDataField","持仓量","TThostFtdcLargeVolumeType", "OpenInterest", &(m_ThostFtdcDepthMarketDataField.OpenInterest));
	RegField("CThostFtdcDepthMarketDataField","今收盘","TThostFtdcPriceType", "ClosePrice", &(m_ThostFtdcDepthMarketDataField.ClosePrice));
	RegField("CThostFtdcDepthMarketDataField","本次结算价","TThostFtdcPriceType", "SettlementPrice", &(m_ThostFtdcDepthMarketDataField.SettlementPrice));
	RegField("CThostFtdcDepthMarketDataField","涨停板价","TThostFtdcPriceType", "UpperLimitPrice", &(m_ThostFtdcDepthMarketDataField.UpperLimitPrice));
	RegField("CThostFtdcDepthMarketDataField","跌停板价","TThostFtdcPriceType", "LowerLimitPrice", &(m_ThostFtdcDepthMarketDataField.LowerLimitPrice));
	RegField("CThostFtdcDepthMarketDataField","昨虚实度","TThostFtdcRatioType", "PreDelta", &(m_ThostFtdcDepthMarketDataField.PreDelta));
	RegField("CThostFtdcDepthMarketDataField","今虚实度","TThostFtdcRatioType", "CurrDelta", &(m_ThostFtdcDepthMarketDataField.CurrDelta));
	RegField("CThostFtdcDepthMarketDataField","最后修改时间","TThostFtdcTimeType", "UpdateTime", &(m_ThostFtdcDepthMarketDataField.UpdateTime));
	RegField("CThostFtdcDepthMarketDataField","最后修改毫秒","TThostFtdcMillisecType", "UpdateMillisec", &(m_ThostFtdcDepthMarketDataField.UpdateMillisec));
	RegField("CThostFtdcDepthMarketDataField","申买价一","TThostFtdcPriceType", "BidPrice1", &(m_ThostFtdcDepthMarketDataField.BidPrice1));
	RegField("CThostFtdcDepthMarketDataField","申买量一","TThostFtdcVolumeType", "BidVolume1", &(m_ThostFtdcDepthMarketDataField.BidVolume1));
	RegField("CThostFtdcDepthMarketDataField","申卖价一","TThostFtdcPriceType", "AskPrice1", &(m_ThostFtdcDepthMarketDataField.AskPrice1));
	RegField("CThostFtdcDepthMarketDataField","申卖量一","TThostFtdcVolumeType", "AskVolume1", &(m_ThostFtdcDepthMarketDataField.AskVolume1));
	RegField("CThostFtdcDepthMarketDataField","申买价二","TThostFtdcPriceType", "BidPrice2", &(m_ThostFtdcDepthMarketDataField.BidPrice2));
	RegField("CThostFtdcDepthMarketDataField","申买量二","TThostFtdcVolumeType", "BidVolume2", &(m_ThostFtdcDepthMarketDataField.BidVolume2));
	RegField("CThostFtdcDepthMarketDataField","申卖价二","TThostFtdcPriceType", "AskPrice2", &(m_ThostFtdcDepthMarketDataField.AskPrice2));
	RegField("CThostFtdcDepthMarketDataField","申卖量二","TThostFtdcVolumeType", "AskVolume2", &(m_ThostFtdcDepthMarketDataField.AskVolume2));
	RegField("CThostFtdcDepthMarketDataField","申买价三","TThostFtdcPriceType", "BidPrice3", &(m_ThostFtdcDepthMarketDataField.BidPrice3));
	RegField("CThostFtdcDepthMarketDataField","申买量三","TThostFtdcVolumeType", "BidVolume3", &(m_ThostFtdcDepthMarketDataField.BidVolume3));
	RegField("CThostFtdcDepthMarketDataField","申卖价三","TThostFtdcPriceType", "AskPrice3", &(m_ThostFtdcDepthMarketDataField.AskPrice3));
	RegField("CThostFtdcDepthMarketDataField","申卖量三","TThostFtdcVolumeType", "AskVolume3", &(m_ThostFtdcDepthMarketDataField.AskVolume3));
	RegField("CThostFtdcDepthMarketDataField","申买价四","TThostFtdcPriceType", "BidPrice4", &(m_ThostFtdcDepthMarketDataField.BidPrice4));
	RegField("CThostFtdcDepthMarketDataField","申买量四","TThostFtdcVolumeType", "BidVolume4", &(m_ThostFtdcDepthMarketDataField.BidVolume4));
	RegField("CThostFtdcDepthMarketDataField","申卖价四","TThostFtdcPriceType", "AskPrice4", &(m_ThostFtdcDepthMarketDataField.AskPrice4));
	RegField("CThostFtdcDepthMarketDataField","申卖量四","TThostFtdcVolumeType", "AskVolume4", &(m_ThostFtdcDepthMarketDataField.AskVolume4));
	RegField("CThostFtdcDepthMarketDataField","申买价五","TThostFtdcPriceType", "BidPrice5", &(m_ThostFtdcDepthMarketDataField.BidPrice5));
	RegField("CThostFtdcDepthMarketDataField","申买量五","TThostFtdcVolumeType", "BidVolume5", &(m_ThostFtdcDepthMarketDataField.BidVolume5));
	RegField("CThostFtdcDepthMarketDataField","申卖价五","TThostFtdcPriceType", "AskPrice5", &(m_ThostFtdcDepthMarketDataField.AskPrice5));
	RegField("CThostFtdcDepthMarketDataField","申卖量五","TThostFtdcVolumeType", "AskVolume5", &(m_ThostFtdcDepthMarketDataField.AskVolume5));
	RegField("CThostFtdcDepthMarketDataField","当日均价","TThostFtdcPriceType", "AveragePrice", &(m_ThostFtdcDepthMarketDataField.AveragePrice));
	RegField("CThostFtdcDepthMarketDataField","业务日期","TThostFtdcDateType", "ActionDay", &(m_ThostFtdcDepthMarketDataField.ActionDay));

	RegField("CThostFtdcInstrumentTradingRightField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInstrumentTradingRightField.InstrumentID));
	RegField("CThostFtdcInstrumentTradingRightField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcInstrumentTradingRightField.InvestorRange));
	RegField("CThostFtdcInstrumentTradingRightField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInstrumentTradingRightField.BrokerID));
	RegField("CThostFtdcInstrumentTradingRightField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInstrumentTradingRightField.InvestorID));
	RegField("CThostFtdcInstrumentTradingRightField","交易权限","TThostFtdcTradingRightType", "TradingRight", &(m_ThostFtdcInstrumentTradingRightField.TradingRight));

	RegField("CThostFtdcBrokerUserField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerUserField.BrokerID));
	RegField("CThostFtdcBrokerUserField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcBrokerUserField.UserID));
	RegField("CThostFtdcBrokerUserField","用户名称","TThostFtdcUserNameType", "UserName", &(m_ThostFtdcBrokerUserField.UserName));
	RegField("CThostFtdcBrokerUserField","用户类型","TThostFtdcUserTypeType", "UserType", &(m_ThostFtdcBrokerUserField.UserType));
	RegField("CThostFtdcBrokerUserField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcBrokerUserField.IsActive));
	RegField("CThostFtdcBrokerUserField","是否使用令牌","TThostFtdcBoolType", "IsUsingOTP", &(m_ThostFtdcBrokerUserField.IsUsingOTP));

	RegField("CThostFtdcBrokerUserPasswordField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerUserPasswordField.BrokerID));
	RegField("CThostFtdcBrokerUserPasswordField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcBrokerUserPasswordField.UserID));
	RegField("CThostFtdcBrokerUserPasswordField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcBrokerUserPasswordField.Password));

	RegField("CThostFtdcBrokerUserFunctionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerUserFunctionField.BrokerID));
	RegField("CThostFtdcBrokerUserFunctionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcBrokerUserFunctionField.UserID));
	RegField("CThostFtdcBrokerUserFunctionField","经纪公司功能代码","TThostFtdcBrokerFunctionCodeType", "BrokerFunctionCode", &(m_ThostFtdcBrokerUserFunctionField.BrokerFunctionCode));

	RegField("CThostFtdcTraderOfferField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcTraderOfferField.ExchangeID));
	RegField("CThostFtdcTraderOfferField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcTraderOfferField.TraderID));
	RegField("CThostFtdcTraderOfferField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcTraderOfferField.ParticipantID));
	RegField("CThostFtdcTraderOfferField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcTraderOfferField.Password));
	RegField("CThostFtdcTraderOfferField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcTraderOfferField.InstallID));
	RegField("CThostFtdcTraderOfferField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcTraderOfferField.OrderLocalID));
	RegField("CThostFtdcTraderOfferField","交易所交易员连接状态","TThostFtdcTraderConnectStatusType", "TraderConnectStatus", &(m_ThostFtdcTraderOfferField.TraderConnectStatus));
	RegField("CThostFtdcTraderOfferField","发出连接请求的日期","TThostFtdcDateType", "ConnectRequestDate", &(m_ThostFtdcTraderOfferField.ConnectRequestDate));
	RegField("CThostFtdcTraderOfferField","发出连接请求的时间","TThostFtdcTimeType", "ConnectRequestTime", &(m_ThostFtdcTraderOfferField.ConnectRequestTime));
	RegField("CThostFtdcTraderOfferField","上次报告日期","TThostFtdcDateType", "LastReportDate", &(m_ThostFtdcTraderOfferField.LastReportDate));
	RegField("CThostFtdcTraderOfferField","上次报告时间","TThostFtdcTimeType", "LastReportTime", &(m_ThostFtdcTraderOfferField.LastReportTime));
	RegField("CThostFtdcTraderOfferField","完成连接日期","TThostFtdcDateType", "ConnectDate", &(m_ThostFtdcTraderOfferField.ConnectDate));
	RegField("CThostFtdcTraderOfferField","完成连接时间","TThostFtdcTimeType", "ConnectTime", &(m_ThostFtdcTraderOfferField.ConnectTime));
	RegField("CThostFtdcTraderOfferField","启动日期","TThostFtdcDateType", "StartDate", &(m_ThostFtdcTraderOfferField.StartDate));
	RegField("CThostFtdcTraderOfferField","启动时间","TThostFtdcTimeType", "StartTime", &(m_ThostFtdcTraderOfferField.StartTime));
	RegField("CThostFtdcTraderOfferField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcTraderOfferField.TradingDay));
	RegField("CThostFtdcTraderOfferField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTraderOfferField.BrokerID));
	RegField("CThostFtdcTraderOfferField","本席位最大成交编号","TThostFtdcTradeIDType", "MaxTradeID", &(m_ThostFtdcTraderOfferField.MaxTradeID));
	RegField("CThostFtdcTraderOfferField","本席位最大报单备拷","TThostFtdcReturnCodeType", "MaxOrderMessageReference", &(m_ThostFtdcTraderOfferField.MaxOrderMessageReference));

	RegField("CThostFtdcSettlementInfoField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcSettlementInfoField.TradingDay));
	RegField("CThostFtdcSettlementInfoField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcSettlementInfoField.SettlementID));
	RegField("CThostFtdcSettlementInfoField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSettlementInfoField.BrokerID));
	RegField("CThostFtdcSettlementInfoField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSettlementInfoField.InvestorID));
	RegField("CThostFtdcSettlementInfoField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcSettlementInfoField.SequenceNo));
	RegField("CThostFtdcSettlementInfoField","消息正文","TThostFtdcContentType", "Content", &(m_ThostFtdcSettlementInfoField.Content));

	RegField("CThostFtdcInstrumentMarginRateAdjustField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInstrumentMarginRateAdjustField.InstrumentID));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcInstrumentMarginRateAdjustField.InvestorRange));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInstrumentMarginRateAdjustField.BrokerID));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInstrumentMarginRateAdjustField.InvestorID));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcInstrumentMarginRateAdjustField.HedgeFlag));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","多头保证金率","TThostFtdcRatioType", "LongMarginRatioByMoney", &(m_ThostFtdcInstrumentMarginRateAdjustField.LongMarginRatioByMoney));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","多头保证金费","TThostFtdcMoneyType", "LongMarginRatioByVolume", &(m_ThostFtdcInstrumentMarginRateAdjustField.LongMarginRatioByVolume));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","空头保证金率","TThostFtdcRatioType", "ShortMarginRatioByMoney", &(m_ThostFtdcInstrumentMarginRateAdjustField.ShortMarginRatioByMoney));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","空头保证金费","TThostFtdcMoneyType", "ShortMarginRatioByVolume", &(m_ThostFtdcInstrumentMarginRateAdjustField.ShortMarginRatioByVolume));
	RegField("CThostFtdcInstrumentMarginRateAdjustField","是否相对交易所收取","TThostFtdcBoolType", "IsRelative", &(m_ThostFtdcInstrumentMarginRateAdjustField.IsRelative));

	RegField("CThostFtdcExchangeMarginRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcExchangeMarginRateField.BrokerID));
	RegField("CThostFtdcExchangeMarginRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcExchangeMarginRateField.InstrumentID));
	RegField("CThostFtdcExchangeMarginRateField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcExchangeMarginRateField.HedgeFlag));
	RegField("CThostFtdcExchangeMarginRateField","多头保证金率","TThostFtdcRatioType", "LongMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateField.LongMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateField","多头保证金费","TThostFtdcMoneyType", "LongMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateField.LongMarginRatioByVolume));
	RegField("CThostFtdcExchangeMarginRateField","空头保证金率","TThostFtdcRatioType", "ShortMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateField.ShortMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateField","空头保证金费","TThostFtdcMoneyType", "ShortMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateField.ShortMarginRatioByVolume));

	RegField("CThostFtdcExchangeMarginRateAdjustField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcExchangeMarginRateAdjustField.BrokerID));
	RegField("CThostFtdcExchangeMarginRateAdjustField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcExchangeMarginRateAdjustField.InstrumentID));
	RegField("CThostFtdcExchangeMarginRateAdjustField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcExchangeMarginRateAdjustField.HedgeFlag));
	RegField("CThostFtdcExchangeMarginRateAdjustField","跟随交易所投资者多头保证金率","TThostFtdcRatioType", "LongMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateAdjustField.LongMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateAdjustField","跟随交易所投资者多头保证金费","TThostFtdcMoneyType", "LongMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateAdjustField.LongMarginRatioByVolume));
	RegField("CThostFtdcExchangeMarginRateAdjustField","跟随交易所投资者空头保证金率","TThostFtdcRatioType", "ShortMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateAdjustField.ShortMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateAdjustField","跟随交易所投资者空头保证金费","TThostFtdcMoneyType", "ShortMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateAdjustField.ShortMarginRatioByVolume));
	RegField("CThostFtdcExchangeMarginRateAdjustField","交易所多头保证金率","TThostFtdcRatioType", "ExchLongMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateAdjustField.ExchLongMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateAdjustField","交易所多头保证金费","TThostFtdcMoneyType", "ExchLongMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateAdjustField.ExchLongMarginRatioByVolume));
	RegField("CThostFtdcExchangeMarginRateAdjustField","交易所空头保证金率","TThostFtdcRatioType", "ExchShortMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateAdjustField.ExchShortMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateAdjustField","交易所空头保证金费","TThostFtdcMoneyType", "ExchShortMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateAdjustField.ExchShortMarginRatioByVolume));
	RegField("CThostFtdcExchangeMarginRateAdjustField","不跟随交易所投资者多头保证金率","TThostFtdcRatioType", "NoLongMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateAdjustField.NoLongMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateAdjustField","不跟随交易所投资者多头保证金费","TThostFtdcMoneyType", "NoLongMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateAdjustField.NoLongMarginRatioByVolume));
	RegField("CThostFtdcExchangeMarginRateAdjustField","不跟随交易所投资者空头保证金率","TThostFtdcRatioType", "NoShortMarginRatioByMoney", &(m_ThostFtdcExchangeMarginRateAdjustField.NoShortMarginRatioByMoney));
	RegField("CThostFtdcExchangeMarginRateAdjustField","不跟随交易所投资者空头保证金费","TThostFtdcMoneyType", "NoShortMarginRatioByVolume", &(m_ThostFtdcExchangeMarginRateAdjustField.NoShortMarginRatioByVolume));

	RegField("CThostFtdcExchangeRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcExchangeRateField.BrokerID));
	RegField("CThostFtdcExchangeRateField","源币种","TThostFtdcCurrencyIDType", "FromCurrencyID", &(m_ThostFtdcExchangeRateField.FromCurrencyID));
	RegField("CThostFtdcExchangeRateField","源币种单位数量","TThostFtdcCurrencyUnitType", "FromCurrencyUnit", &(m_ThostFtdcExchangeRateField.FromCurrencyUnit));
	RegField("CThostFtdcExchangeRateField","目标币种","TThostFtdcCurrencyIDType", "ToCurrencyID", &(m_ThostFtdcExchangeRateField.ToCurrencyID));
	RegField("CThostFtdcExchangeRateField","汇率","TThostFtdcExchangeRateType", "ExchangeRate", &(m_ThostFtdcExchangeRateField.ExchangeRate));

	RegField("CThostFtdcSettlementRefField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcSettlementRefField.TradingDay));
	RegField("CThostFtdcSettlementRefField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcSettlementRefField.SettlementID));

	RegField("CThostFtdcCurrentTimeField","当前日期","TThostFtdcDateType", "CurrDate", &(m_ThostFtdcCurrentTimeField.CurrDate));
	RegField("CThostFtdcCurrentTimeField","当前时间","TThostFtdcTimeType", "CurrTime", &(m_ThostFtdcCurrentTimeField.CurrTime));
	RegField("CThostFtdcCurrentTimeField","当前时间（毫秒）","TThostFtdcMillisecType", "CurrMillisec", &(m_ThostFtdcCurrentTimeField.CurrMillisec));
	RegField("CThostFtdcCurrentTimeField","业务日期","TThostFtdcDateType", "ActionDay", &(m_ThostFtdcCurrentTimeField.ActionDay));

	RegField("CThostFtdcCommPhaseField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcCommPhaseField.TradingDay));
	RegField("CThostFtdcCommPhaseField","通讯时段编号","TThostFtdcCommPhaseNoType", "CommPhaseNo", &(m_ThostFtdcCommPhaseField.CommPhaseNo));
	RegField("CThostFtdcCommPhaseField","系统编号","TThostFtdcSystemIDType", "SystemID", &(m_ThostFtdcCommPhaseField.SystemID));

	RegField("CThostFtdcLoginInfoField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcLoginInfoField.FrontID));
	RegField("CThostFtdcLoginInfoField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcLoginInfoField.SessionID));
	RegField("CThostFtdcLoginInfoField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcLoginInfoField.BrokerID));
	RegField("CThostFtdcLoginInfoField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcLoginInfoField.UserID));
	RegField("CThostFtdcLoginInfoField","登录日期","TThostFtdcDateType", "LoginDate", &(m_ThostFtdcLoginInfoField.LoginDate));
	RegField("CThostFtdcLoginInfoField","登录时间","TThostFtdcTimeType", "LoginTime", &(m_ThostFtdcLoginInfoField.LoginTime));
	RegField("CThostFtdcLoginInfoField","IP地址","TThostFtdcIPAddressType", "IPAddress", &(m_ThostFtdcLoginInfoField.IPAddress));
	RegField("CThostFtdcLoginInfoField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcLoginInfoField.UserProductInfo));
	RegField("CThostFtdcLoginInfoField","接口端产品信息","TThostFtdcProductInfoType", "InterfaceProductInfo", &(m_ThostFtdcLoginInfoField.InterfaceProductInfo));
	RegField("CThostFtdcLoginInfoField","协议信息","TThostFtdcProtocolInfoType", "ProtocolInfo", &(m_ThostFtdcLoginInfoField.ProtocolInfo));
	RegField("CThostFtdcLoginInfoField","系统名称","TThostFtdcSystemNameType", "SystemName", &(m_ThostFtdcLoginInfoField.SystemName));
	RegField("CThostFtdcLoginInfoField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcLoginInfoField.Password));
	RegField("CThostFtdcLoginInfoField","最大报单引用","TThostFtdcOrderRefType", "MaxOrderRef", &(m_ThostFtdcLoginInfoField.MaxOrderRef));
	RegField("CThostFtdcLoginInfoField","上期所时间","TThostFtdcTimeType", "SHFETime", &(m_ThostFtdcLoginInfoField.SHFETime));
	RegField("CThostFtdcLoginInfoField","大商所时间","TThostFtdcTimeType", "DCETime", &(m_ThostFtdcLoginInfoField.DCETime));
	RegField("CThostFtdcLoginInfoField","郑商所时间","TThostFtdcTimeType", "CZCETime", &(m_ThostFtdcLoginInfoField.CZCETime));
	RegField("CThostFtdcLoginInfoField","中金所时间","TThostFtdcTimeType", "FFEXTime", &(m_ThostFtdcLoginInfoField.FFEXTime));
	RegField("CThostFtdcLoginInfoField","Mac地址","TThostFtdcMacAddressType", "MacAddress", &(m_ThostFtdcLoginInfoField.MacAddress));
	RegField("CThostFtdcLoginInfoField","动态密码","TThostFtdcPasswordType", "OneTimePassword", &(m_ThostFtdcLoginInfoField.OneTimePassword));
	RegField("CThostFtdcLoginInfoField","能源中心时间","TThostFtdcTimeType", "INETime", &(m_ThostFtdcLoginInfoField.INETime));

	RegField("CThostFtdcLogoutAllField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcLogoutAllField.FrontID));
	RegField("CThostFtdcLogoutAllField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcLogoutAllField.SessionID));
	RegField("CThostFtdcLogoutAllField","系统名称","TThostFtdcSystemNameType", "SystemName", &(m_ThostFtdcLogoutAllField.SystemName));

	RegField("CThostFtdcFrontStatusField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcFrontStatusField.FrontID));
	RegField("CThostFtdcFrontStatusField","上次报告日期","TThostFtdcDateType", "LastReportDate", &(m_ThostFtdcFrontStatusField.LastReportDate));
	RegField("CThostFtdcFrontStatusField","上次报告时间","TThostFtdcTimeType", "LastReportTime", &(m_ThostFtdcFrontStatusField.LastReportTime));
	RegField("CThostFtdcFrontStatusField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcFrontStatusField.IsActive));

	RegField("CThostFtdcUserPasswordUpdateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcUserPasswordUpdateField.BrokerID));
	RegField("CThostFtdcUserPasswordUpdateField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcUserPasswordUpdateField.UserID));
	RegField("CThostFtdcUserPasswordUpdateField","原来的口令","TThostFtdcPasswordType", "OldPassword", &(m_ThostFtdcUserPasswordUpdateField.OldPassword));
	RegField("CThostFtdcUserPasswordUpdateField","新的口令","TThostFtdcPasswordType", "NewPassword", &(m_ThostFtdcUserPasswordUpdateField.NewPassword));

	RegField("CThostFtdcInputOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInputOrderField.BrokerID));
	RegField("CThostFtdcInputOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInputOrderField.InvestorID));
	RegField("CThostFtdcInputOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInputOrderField.InstrumentID));
	RegField("CThostFtdcInputOrderField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcInputOrderField.OrderRef));
	RegField("CThostFtdcInputOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcInputOrderField.UserID));
	RegField("CThostFtdcInputOrderField","报单价格条件","TThostFtdcOrderPriceTypeType", "OrderPriceType", &(m_ThostFtdcInputOrderField.OrderPriceType));
	RegField("CThostFtdcInputOrderField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcInputOrderField.Direction));
	RegField("CThostFtdcInputOrderField","组合开平标志","TThostFtdcCombOffsetFlagType", "CombOffsetFlag", &(m_ThostFtdcInputOrderField.CombOffsetFlag));
	RegField("CThostFtdcInputOrderField","组合投机套保标志","TThostFtdcCombHedgeFlagType", "CombHedgeFlag", &(m_ThostFtdcInputOrderField.CombHedgeFlag));
	RegField("CThostFtdcInputOrderField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcInputOrderField.LimitPrice));
	RegField("CThostFtdcInputOrderField","数量","TThostFtdcVolumeType", "VolumeTotalOriginal", &(m_ThostFtdcInputOrderField.VolumeTotalOriginal));
	RegField("CThostFtdcInputOrderField","有效期类型","TThostFtdcTimeConditionType", "TimeCondition", &(m_ThostFtdcInputOrderField.TimeCondition));
	RegField("CThostFtdcInputOrderField","GTD日期","TThostFtdcDateType", "GTDDate", &(m_ThostFtdcInputOrderField.GTDDate));
	RegField("CThostFtdcInputOrderField","成交量类型","TThostFtdcVolumeConditionType", "VolumeCondition", &(m_ThostFtdcInputOrderField.VolumeCondition));
	RegField("CThostFtdcInputOrderField","最小成交量","TThostFtdcVolumeType", "MinVolume", &(m_ThostFtdcInputOrderField.MinVolume));
	RegField("CThostFtdcInputOrderField","触发条件","TThostFtdcContingentConditionType", "ContingentCondition", &(m_ThostFtdcInputOrderField.ContingentCondition));
	RegField("CThostFtdcInputOrderField","止损价","TThostFtdcPriceType", "StopPrice", &(m_ThostFtdcInputOrderField.StopPrice));
	RegField("CThostFtdcInputOrderField","强平原因","TThostFtdcForceCloseReasonType", "ForceCloseReason", &(m_ThostFtdcInputOrderField.ForceCloseReason));
	RegField("CThostFtdcInputOrderField","自动挂起标志","TThostFtdcBoolType", "IsAutoSuspend", &(m_ThostFtdcInputOrderField.IsAutoSuspend));
	RegField("CThostFtdcInputOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcInputOrderField.BusinessUnit));
	RegField("CThostFtdcInputOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcInputOrderField.RequestID));
	RegField("CThostFtdcInputOrderField","用户强评标志","TThostFtdcBoolType", "UserForceClose", &(m_ThostFtdcInputOrderField.UserForceClose));
	RegField("CThostFtdcInputOrderField","互换单标志","TThostFtdcBoolType", "IsSwapOrder", &(m_ThostFtdcInputOrderField.IsSwapOrder));

	RegField("CThostFtdcOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOrderField.BrokerID));
	RegField("CThostFtdcOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOrderField.InvestorID));
	RegField("CThostFtdcOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOrderField.InstrumentID));
	RegField("CThostFtdcOrderField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcOrderField.OrderRef));
	RegField("CThostFtdcOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcOrderField.UserID));
	RegField("CThostFtdcOrderField","报单价格条件","TThostFtdcOrderPriceTypeType", "OrderPriceType", &(m_ThostFtdcOrderField.OrderPriceType));
	RegField("CThostFtdcOrderField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcOrderField.Direction));
	RegField("CThostFtdcOrderField","组合开平标志","TThostFtdcCombOffsetFlagType", "CombOffsetFlag", &(m_ThostFtdcOrderField.CombOffsetFlag));
	RegField("CThostFtdcOrderField","组合投机套保标志","TThostFtdcCombHedgeFlagType", "CombHedgeFlag", &(m_ThostFtdcOrderField.CombHedgeFlag));
	RegField("CThostFtdcOrderField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcOrderField.LimitPrice));
	RegField("CThostFtdcOrderField","数量","TThostFtdcVolumeType", "VolumeTotalOriginal", &(m_ThostFtdcOrderField.VolumeTotalOriginal));
	RegField("CThostFtdcOrderField","有效期类型","TThostFtdcTimeConditionType", "TimeCondition", &(m_ThostFtdcOrderField.TimeCondition));
	RegField("CThostFtdcOrderField","GTD日期","TThostFtdcDateType", "GTDDate", &(m_ThostFtdcOrderField.GTDDate));
	RegField("CThostFtdcOrderField","成交量类型","TThostFtdcVolumeConditionType", "VolumeCondition", &(m_ThostFtdcOrderField.VolumeCondition));
	RegField("CThostFtdcOrderField","最小成交量","TThostFtdcVolumeType", "MinVolume", &(m_ThostFtdcOrderField.MinVolume));
	RegField("CThostFtdcOrderField","触发条件","TThostFtdcContingentConditionType", "ContingentCondition", &(m_ThostFtdcOrderField.ContingentCondition));
	RegField("CThostFtdcOrderField","止损价","TThostFtdcPriceType", "StopPrice", &(m_ThostFtdcOrderField.StopPrice));
	RegField("CThostFtdcOrderField","强平原因","TThostFtdcForceCloseReasonType", "ForceCloseReason", &(m_ThostFtdcOrderField.ForceCloseReason));
	RegField("CThostFtdcOrderField","自动挂起标志","TThostFtdcBoolType", "IsAutoSuspend", &(m_ThostFtdcOrderField.IsAutoSuspend));
	RegField("CThostFtdcOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcOrderField.BusinessUnit));
	RegField("CThostFtdcOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcOrderField.RequestID));
	RegField("CThostFtdcOrderField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcOrderField.OrderLocalID));
	RegField("CThostFtdcOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcOrderField.ExchangeID));
	RegField("CThostFtdcOrderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcOrderField.ParticipantID));
	RegField("CThostFtdcOrderField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcOrderField.ClientID));
	RegField("CThostFtdcOrderField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcOrderField.ExchangeInstID));
	RegField("CThostFtdcOrderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcOrderField.TraderID));
	RegField("CThostFtdcOrderField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcOrderField.InstallID));
	RegField("CThostFtdcOrderField","报单提交状态","TThostFtdcOrderSubmitStatusType", "OrderSubmitStatus", &(m_ThostFtdcOrderField.OrderSubmitStatus));
	RegField("CThostFtdcOrderField","报单提示序号","TThostFtdcSequenceNoType", "NotifySequence", &(m_ThostFtdcOrderField.NotifySequence));
	RegField("CThostFtdcOrderField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcOrderField.TradingDay));
	RegField("CThostFtdcOrderField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcOrderField.SettlementID));
	RegField("CThostFtdcOrderField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcOrderField.OrderSysID));
	RegField("CThostFtdcOrderField","报单来源","TThostFtdcOrderSourceType", "OrderSource", &(m_ThostFtdcOrderField.OrderSource));
	RegField("CThostFtdcOrderField","报单状态","TThostFtdcOrderStatusType", "OrderStatus", &(m_ThostFtdcOrderField.OrderStatus));
	RegField("CThostFtdcOrderField","报单类型","TThostFtdcOrderTypeType", "OrderType", &(m_ThostFtdcOrderField.OrderType));
	RegField("CThostFtdcOrderField","今成交数量","TThostFtdcVolumeType", "VolumeTraded", &(m_ThostFtdcOrderField.VolumeTraded));
	RegField("CThostFtdcOrderField","剩余数量","TThostFtdcVolumeType", "VolumeTotal", &(m_ThostFtdcOrderField.VolumeTotal));
	RegField("CThostFtdcOrderField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcOrderField.InsertDate));
	RegField("CThostFtdcOrderField","委托时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcOrderField.InsertTime));
	RegField("CThostFtdcOrderField","激活时间","TThostFtdcTimeType", "ActiveTime", &(m_ThostFtdcOrderField.ActiveTime));
	RegField("CThostFtdcOrderField","挂起时间","TThostFtdcTimeType", "SuspendTime", &(m_ThostFtdcOrderField.SuspendTime));
	RegField("CThostFtdcOrderField","最后修改时间","TThostFtdcTimeType", "UpdateTime", &(m_ThostFtdcOrderField.UpdateTime));
	RegField("CThostFtdcOrderField","撤销时间","TThostFtdcTimeType", "CancelTime", &(m_ThostFtdcOrderField.CancelTime));
	RegField("CThostFtdcOrderField","最后修改交易所交易员代码","TThostFtdcTraderIDType", "ActiveTraderID", &(m_ThostFtdcOrderField.ActiveTraderID));
	RegField("CThostFtdcOrderField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcOrderField.ClearingPartID));
	RegField("CThostFtdcOrderField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcOrderField.SequenceNo));
	RegField("CThostFtdcOrderField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcOrderField.FrontID));
	RegField("CThostFtdcOrderField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcOrderField.SessionID));
	RegField("CThostFtdcOrderField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcOrderField.UserProductInfo));
	RegField("CThostFtdcOrderField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcOrderField.StatusMsg));
	RegField("CThostFtdcOrderField","用户强评标志","TThostFtdcBoolType", "UserForceClose", &(m_ThostFtdcOrderField.UserForceClose));
	RegField("CThostFtdcOrderField","操作用户代码","TThostFtdcUserIDType", "ActiveUserID", &(m_ThostFtdcOrderField.ActiveUserID));
	RegField("CThostFtdcOrderField","经纪公司报单编号","TThostFtdcSequenceNoType", "BrokerOrderSeq", &(m_ThostFtdcOrderField.BrokerOrderSeq));
	RegField("CThostFtdcOrderField","相关报单","TThostFtdcOrderSysIDType", "RelativeOrderSysID", &(m_ThostFtdcOrderField.RelativeOrderSysID));
	RegField("CThostFtdcOrderField","郑商所成交数量","TThostFtdcVolumeType", "ZCETotalTradedVolume", &(m_ThostFtdcOrderField.ZCETotalTradedVolume));
	RegField("CThostFtdcOrderField","互换单标志","TThostFtdcBoolType", "IsSwapOrder", &(m_ThostFtdcOrderField.IsSwapOrder));

	RegField("CThostFtdcExchangeOrderField","报单价格条件","TThostFtdcOrderPriceTypeType", "OrderPriceType", &(m_ThostFtdcExchangeOrderField.OrderPriceType));
	RegField("CThostFtdcExchangeOrderField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcExchangeOrderField.Direction));
	RegField("CThostFtdcExchangeOrderField","组合开平标志","TThostFtdcCombOffsetFlagType", "CombOffsetFlag", &(m_ThostFtdcExchangeOrderField.CombOffsetFlag));
	RegField("CThostFtdcExchangeOrderField","组合投机套保标志","TThostFtdcCombHedgeFlagType", "CombHedgeFlag", &(m_ThostFtdcExchangeOrderField.CombHedgeFlag));
	RegField("CThostFtdcExchangeOrderField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcExchangeOrderField.LimitPrice));
	RegField("CThostFtdcExchangeOrderField","数量","TThostFtdcVolumeType", "VolumeTotalOriginal", &(m_ThostFtdcExchangeOrderField.VolumeTotalOriginal));
	RegField("CThostFtdcExchangeOrderField","有效期类型","TThostFtdcTimeConditionType", "TimeCondition", &(m_ThostFtdcExchangeOrderField.TimeCondition));
	RegField("CThostFtdcExchangeOrderField","GTD日期","TThostFtdcDateType", "GTDDate", &(m_ThostFtdcExchangeOrderField.GTDDate));
	RegField("CThostFtdcExchangeOrderField","成交量类型","TThostFtdcVolumeConditionType", "VolumeCondition", &(m_ThostFtdcExchangeOrderField.VolumeCondition));
	RegField("CThostFtdcExchangeOrderField","最小成交量","TThostFtdcVolumeType", "MinVolume", &(m_ThostFtdcExchangeOrderField.MinVolume));
	RegField("CThostFtdcExchangeOrderField","触发条件","TThostFtdcContingentConditionType", "ContingentCondition", &(m_ThostFtdcExchangeOrderField.ContingentCondition));
	RegField("CThostFtdcExchangeOrderField","止损价","TThostFtdcPriceType", "StopPrice", &(m_ThostFtdcExchangeOrderField.StopPrice));
	RegField("CThostFtdcExchangeOrderField","强平原因","TThostFtdcForceCloseReasonType", "ForceCloseReason", &(m_ThostFtdcExchangeOrderField.ForceCloseReason));
	RegField("CThostFtdcExchangeOrderField","自动挂起标志","TThostFtdcBoolType", "IsAutoSuspend", &(m_ThostFtdcExchangeOrderField.IsAutoSuspend));
	RegField("CThostFtdcExchangeOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExchangeOrderField.BusinessUnit));
	RegField("CThostFtdcExchangeOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcExchangeOrderField.RequestID));
	RegField("CThostFtdcExchangeOrderField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcExchangeOrderField.OrderLocalID));
	RegField("CThostFtdcExchangeOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeOrderField.ExchangeID));
	RegField("CThostFtdcExchangeOrderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeOrderField.ParticipantID));
	RegField("CThostFtdcExchangeOrderField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeOrderField.ClientID));
	RegField("CThostFtdcExchangeOrderField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcExchangeOrderField.ExchangeInstID));
	RegField("CThostFtdcExchangeOrderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeOrderField.TraderID));
	RegField("CThostFtdcExchangeOrderField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeOrderField.InstallID));
	RegField("CThostFtdcExchangeOrderField","报单提交状态","TThostFtdcOrderSubmitStatusType", "OrderSubmitStatus", &(m_ThostFtdcExchangeOrderField.OrderSubmitStatus));
	RegField("CThostFtdcExchangeOrderField","报单提示序号","TThostFtdcSequenceNoType", "NotifySequence", &(m_ThostFtdcExchangeOrderField.NotifySequence));
	RegField("CThostFtdcExchangeOrderField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcExchangeOrderField.TradingDay));
	RegField("CThostFtdcExchangeOrderField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcExchangeOrderField.SettlementID));
	RegField("CThostFtdcExchangeOrderField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcExchangeOrderField.OrderSysID));
	RegField("CThostFtdcExchangeOrderField","报单来源","TThostFtdcOrderSourceType", "OrderSource", &(m_ThostFtdcExchangeOrderField.OrderSource));
	RegField("CThostFtdcExchangeOrderField","报单状态","TThostFtdcOrderStatusType", "OrderStatus", &(m_ThostFtdcExchangeOrderField.OrderStatus));
	RegField("CThostFtdcExchangeOrderField","报单类型","TThostFtdcOrderTypeType", "OrderType", &(m_ThostFtdcExchangeOrderField.OrderType));
	RegField("CThostFtdcExchangeOrderField","今成交数量","TThostFtdcVolumeType", "VolumeTraded", &(m_ThostFtdcExchangeOrderField.VolumeTraded));
	RegField("CThostFtdcExchangeOrderField","剩余数量","TThostFtdcVolumeType", "VolumeTotal", &(m_ThostFtdcExchangeOrderField.VolumeTotal));
	RegField("CThostFtdcExchangeOrderField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcExchangeOrderField.InsertDate));
	RegField("CThostFtdcExchangeOrderField","委托时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcExchangeOrderField.InsertTime));
	RegField("CThostFtdcExchangeOrderField","激活时间","TThostFtdcTimeType", "ActiveTime", &(m_ThostFtdcExchangeOrderField.ActiveTime));
	RegField("CThostFtdcExchangeOrderField","挂起时间","TThostFtdcTimeType", "SuspendTime", &(m_ThostFtdcExchangeOrderField.SuspendTime));
	RegField("CThostFtdcExchangeOrderField","最后修改时间","TThostFtdcTimeType", "UpdateTime", &(m_ThostFtdcExchangeOrderField.UpdateTime));
	RegField("CThostFtdcExchangeOrderField","撤销时间","TThostFtdcTimeType", "CancelTime", &(m_ThostFtdcExchangeOrderField.CancelTime));
	RegField("CThostFtdcExchangeOrderField","最后修改交易所交易员代码","TThostFtdcTraderIDType", "ActiveTraderID", &(m_ThostFtdcExchangeOrderField.ActiveTraderID));
	RegField("CThostFtdcExchangeOrderField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcExchangeOrderField.ClearingPartID));
	RegField("CThostFtdcExchangeOrderField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcExchangeOrderField.SequenceNo));

	RegField("CThostFtdcExchangeOrderInsertErrorField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeOrderInsertErrorField.ExchangeID));
	RegField("CThostFtdcExchangeOrderInsertErrorField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeOrderInsertErrorField.ParticipantID));
	RegField("CThostFtdcExchangeOrderInsertErrorField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeOrderInsertErrorField.TraderID));
	RegField("CThostFtdcExchangeOrderInsertErrorField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeOrderInsertErrorField.InstallID));
	RegField("CThostFtdcExchangeOrderInsertErrorField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcExchangeOrderInsertErrorField.OrderLocalID));
	RegField("CThostFtdcExchangeOrderInsertErrorField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcExchangeOrderInsertErrorField.ErrorID));
	RegField("CThostFtdcExchangeOrderInsertErrorField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcExchangeOrderInsertErrorField.ErrorMsg));

	RegField("CThostFtdcInputOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInputOrderActionField.BrokerID));
	RegField("CThostFtdcInputOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInputOrderActionField.InvestorID));
	RegField("CThostFtdcInputOrderActionField","报单操作引用","TThostFtdcOrderActionRefType", "OrderActionRef", &(m_ThostFtdcInputOrderActionField.OrderActionRef));
	RegField("CThostFtdcInputOrderActionField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcInputOrderActionField.OrderRef));
	RegField("CThostFtdcInputOrderActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcInputOrderActionField.RequestID));
	RegField("CThostFtdcInputOrderActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcInputOrderActionField.FrontID));
	RegField("CThostFtdcInputOrderActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcInputOrderActionField.SessionID));
	RegField("CThostFtdcInputOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcInputOrderActionField.ExchangeID));
	RegField("CThostFtdcInputOrderActionField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcInputOrderActionField.OrderSysID));
	RegField("CThostFtdcInputOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcInputOrderActionField.ActionFlag));
	RegField("CThostFtdcInputOrderActionField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcInputOrderActionField.LimitPrice));
	RegField("CThostFtdcInputOrderActionField","数量变化","TThostFtdcVolumeType", "VolumeChange", &(m_ThostFtdcInputOrderActionField.VolumeChange));
	RegField("CThostFtdcInputOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcInputOrderActionField.UserID));
	RegField("CThostFtdcInputOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInputOrderActionField.InstrumentID));

	RegField("CThostFtdcOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOrderActionField.BrokerID));
	RegField("CThostFtdcOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOrderActionField.InvestorID));
	RegField("CThostFtdcOrderActionField","报单操作引用","TThostFtdcOrderActionRefType", "OrderActionRef", &(m_ThostFtdcOrderActionField.OrderActionRef));
	RegField("CThostFtdcOrderActionField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcOrderActionField.OrderRef));
	RegField("CThostFtdcOrderActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcOrderActionField.RequestID));
	RegField("CThostFtdcOrderActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcOrderActionField.FrontID));
	RegField("CThostFtdcOrderActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcOrderActionField.SessionID));
	RegField("CThostFtdcOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcOrderActionField.ExchangeID));
	RegField("CThostFtdcOrderActionField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcOrderActionField.OrderSysID));
	RegField("CThostFtdcOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcOrderActionField.ActionFlag));
	RegField("CThostFtdcOrderActionField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcOrderActionField.LimitPrice));
	RegField("CThostFtdcOrderActionField","数量变化","TThostFtdcVolumeType", "VolumeChange", &(m_ThostFtdcOrderActionField.VolumeChange));
	RegField("CThostFtdcOrderActionField","操作日期","TThostFtdcDateType", "ActionDate", &(m_ThostFtdcOrderActionField.ActionDate));
	RegField("CThostFtdcOrderActionField","操作时间","TThostFtdcTimeType", "ActionTime", &(m_ThostFtdcOrderActionField.ActionTime));
	RegField("CThostFtdcOrderActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcOrderActionField.TraderID));
	RegField("CThostFtdcOrderActionField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcOrderActionField.InstallID));
	RegField("CThostFtdcOrderActionField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcOrderActionField.OrderLocalID));
	RegField("CThostFtdcOrderActionField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcOrderActionField.ActionLocalID));
	RegField("CThostFtdcOrderActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcOrderActionField.ParticipantID));
	RegField("CThostFtdcOrderActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcOrderActionField.ClientID));
	RegField("CThostFtdcOrderActionField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcOrderActionField.BusinessUnit));
	RegField("CThostFtdcOrderActionField","报单操作状态","TThostFtdcOrderActionStatusType", "OrderActionStatus", &(m_ThostFtdcOrderActionField.OrderActionStatus));
	RegField("CThostFtdcOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcOrderActionField.UserID));
	RegField("CThostFtdcOrderActionField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcOrderActionField.StatusMsg));
	RegField("CThostFtdcOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOrderActionField.InstrumentID));

	RegField("CThostFtdcExchangeOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeOrderActionField.ExchangeID));
	RegField("CThostFtdcExchangeOrderActionField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcExchangeOrderActionField.OrderSysID));
	RegField("CThostFtdcExchangeOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcExchangeOrderActionField.ActionFlag));
	RegField("CThostFtdcExchangeOrderActionField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcExchangeOrderActionField.LimitPrice));
	RegField("CThostFtdcExchangeOrderActionField","数量变化","TThostFtdcVolumeType", "VolumeChange", &(m_ThostFtdcExchangeOrderActionField.VolumeChange));
	RegField("CThostFtdcExchangeOrderActionField","操作日期","TThostFtdcDateType", "ActionDate", &(m_ThostFtdcExchangeOrderActionField.ActionDate));
	RegField("CThostFtdcExchangeOrderActionField","操作时间","TThostFtdcTimeType", "ActionTime", &(m_ThostFtdcExchangeOrderActionField.ActionTime));
	RegField("CThostFtdcExchangeOrderActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeOrderActionField.TraderID));
	RegField("CThostFtdcExchangeOrderActionField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeOrderActionField.InstallID));
	RegField("CThostFtdcExchangeOrderActionField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcExchangeOrderActionField.OrderLocalID));
	RegField("CThostFtdcExchangeOrderActionField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcExchangeOrderActionField.ActionLocalID));
	RegField("CThostFtdcExchangeOrderActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeOrderActionField.ParticipantID));
	RegField("CThostFtdcExchangeOrderActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeOrderActionField.ClientID));
	RegField("CThostFtdcExchangeOrderActionField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExchangeOrderActionField.BusinessUnit));
	RegField("CThostFtdcExchangeOrderActionField","报单操作状态","TThostFtdcOrderActionStatusType", "OrderActionStatus", &(m_ThostFtdcExchangeOrderActionField.OrderActionStatus));
	RegField("CThostFtdcExchangeOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcExchangeOrderActionField.UserID));

	RegField("CThostFtdcExchangeOrderActionErrorField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeOrderActionErrorField.ExchangeID));
	RegField("CThostFtdcExchangeOrderActionErrorField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcExchangeOrderActionErrorField.OrderSysID));
	RegField("CThostFtdcExchangeOrderActionErrorField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeOrderActionErrorField.TraderID));
	RegField("CThostFtdcExchangeOrderActionErrorField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeOrderActionErrorField.InstallID));
	RegField("CThostFtdcExchangeOrderActionErrorField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcExchangeOrderActionErrorField.OrderLocalID));
	RegField("CThostFtdcExchangeOrderActionErrorField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcExchangeOrderActionErrorField.ActionLocalID));
	RegField("CThostFtdcExchangeOrderActionErrorField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcExchangeOrderActionErrorField.ErrorID));
	RegField("CThostFtdcExchangeOrderActionErrorField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcExchangeOrderActionErrorField.ErrorMsg));

	RegField("CThostFtdcExchangeTradeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeTradeField.ExchangeID));
	RegField("CThostFtdcExchangeTradeField","成交编号","TThostFtdcTradeIDType", "TradeID", &(m_ThostFtdcExchangeTradeField.TradeID));
	RegField("CThostFtdcExchangeTradeField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcExchangeTradeField.Direction));
	RegField("CThostFtdcExchangeTradeField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcExchangeTradeField.OrderSysID));
	RegField("CThostFtdcExchangeTradeField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeTradeField.ParticipantID));
	RegField("CThostFtdcExchangeTradeField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeTradeField.ClientID));
	RegField("CThostFtdcExchangeTradeField","交易角色","TThostFtdcTradingRoleType", "TradingRole", &(m_ThostFtdcExchangeTradeField.TradingRole));
	RegField("CThostFtdcExchangeTradeField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcExchangeTradeField.ExchangeInstID));
	RegField("CThostFtdcExchangeTradeField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcExchangeTradeField.OffsetFlag));
	RegField("CThostFtdcExchangeTradeField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcExchangeTradeField.HedgeFlag));
	RegField("CThostFtdcExchangeTradeField","价格","TThostFtdcPriceType", "Price", &(m_ThostFtdcExchangeTradeField.Price));
	RegField("CThostFtdcExchangeTradeField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcExchangeTradeField.Volume));
	RegField("CThostFtdcExchangeTradeField","成交时期","TThostFtdcDateType", "TradeDate", &(m_ThostFtdcExchangeTradeField.TradeDate));
	RegField("CThostFtdcExchangeTradeField","成交时间","TThostFtdcTimeType", "TradeTime", &(m_ThostFtdcExchangeTradeField.TradeTime));
	RegField("CThostFtdcExchangeTradeField","成交类型","TThostFtdcTradeTypeType", "TradeType", &(m_ThostFtdcExchangeTradeField.TradeType));
	RegField("CThostFtdcExchangeTradeField","成交价来源","TThostFtdcPriceSourceType", "PriceSource", &(m_ThostFtdcExchangeTradeField.PriceSource));
	RegField("CThostFtdcExchangeTradeField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeTradeField.TraderID));
	RegField("CThostFtdcExchangeTradeField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcExchangeTradeField.OrderLocalID));
	RegField("CThostFtdcExchangeTradeField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcExchangeTradeField.ClearingPartID));
	RegField("CThostFtdcExchangeTradeField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExchangeTradeField.BusinessUnit));
	RegField("CThostFtdcExchangeTradeField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcExchangeTradeField.SequenceNo));
	RegField("CThostFtdcExchangeTradeField","成交来源","TThostFtdcTradeSourceType", "TradeSource", &(m_ThostFtdcExchangeTradeField.TradeSource));

	RegField("CThostFtdcTradeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradeField.BrokerID));
	RegField("CThostFtdcTradeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcTradeField.InvestorID));
	RegField("CThostFtdcTradeField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcTradeField.InstrumentID));
	RegField("CThostFtdcTradeField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcTradeField.OrderRef));
	RegField("CThostFtdcTradeField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcTradeField.UserID));
	RegField("CThostFtdcTradeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcTradeField.ExchangeID));
	RegField("CThostFtdcTradeField","成交编号","TThostFtdcTradeIDType", "TradeID", &(m_ThostFtdcTradeField.TradeID));
	RegField("CThostFtdcTradeField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcTradeField.Direction));
	RegField("CThostFtdcTradeField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcTradeField.OrderSysID));
	RegField("CThostFtdcTradeField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcTradeField.ParticipantID));
	RegField("CThostFtdcTradeField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcTradeField.ClientID));
	RegField("CThostFtdcTradeField","交易角色","TThostFtdcTradingRoleType", "TradingRole", &(m_ThostFtdcTradeField.TradingRole));
	RegField("CThostFtdcTradeField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcTradeField.ExchangeInstID));
	RegField("CThostFtdcTradeField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcTradeField.OffsetFlag));
	RegField("CThostFtdcTradeField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcTradeField.HedgeFlag));
	RegField("CThostFtdcTradeField","价格","TThostFtdcPriceType", "Price", &(m_ThostFtdcTradeField.Price));
	RegField("CThostFtdcTradeField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcTradeField.Volume));
	RegField("CThostFtdcTradeField","成交时期","TThostFtdcDateType", "TradeDate", &(m_ThostFtdcTradeField.TradeDate));
	RegField("CThostFtdcTradeField","成交时间","TThostFtdcTimeType", "TradeTime", &(m_ThostFtdcTradeField.TradeTime));
	RegField("CThostFtdcTradeField","成交类型","TThostFtdcTradeTypeType", "TradeType", &(m_ThostFtdcTradeField.TradeType));
	RegField("CThostFtdcTradeField","成交价来源","TThostFtdcPriceSourceType", "PriceSource", &(m_ThostFtdcTradeField.PriceSource));
	RegField("CThostFtdcTradeField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcTradeField.TraderID));
	RegField("CThostFtdcTradeField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcTradeField.OrderLocalID));
	RegField("CThostFtdcTradeField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcTradeField.ClearingPartID));
	RegField("CThostFtdcTradeField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcTradeField.BusinessUnit));
	RegField("CThostFtdcTradeField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcTradeField.SequenceNo));
	RegField("CThostFtdcTradeField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcTradeField.TradingDay));
	RegField("CThostFtdcTradeField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcTradeField.SettlementID));
	RegField("CThostFtdcTradeField","经纪公司报单编号","TThostFtdcSequenceNoType", "BrokerOrderSeq", &(m_ThostFtdcTradeField.BrokerOrderSeq));
	RegField("CThostFtdcTradeField","成交来源","TThostFtdcTradeSourceType", "TradeSource", &(m_ThostFtdcTradeField.TradeSource));

	RegField("CThostFtdcUserSessionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcUserSessionField.FrontID));
	RegField("CThostFtdcUserSessionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcUserSessionField.SessionID));
	RegField("CThostFtdcUserSessionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcUserSessionField.BrokerID));
	RegField("CThostFtdcUserSessionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcUserSessionField.UserID));
	RegField("CThostFtdcUserSessionField","登录日期","TThostFtdcDateType", "LoginDate", &(m_ThostFtdcUserSessionField.LoginDate));
	RegField("CThostFtdcUserSessionField","登录时间","TThostFtdcTimeType", "LoginTime", &(m_ThostFtdcUserSessionField.LoginTime));
	RegField("CThostFtdcUserSessionField","IP地址","TThostFtdcIPAddressType", "IPAddress", &(m_ThostFtdcUserSessionField.IPAddress));
	RegField("CThostFtdcUserSessionField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcUserSessionField.UserProductInfo));
	RegField("CThostFtdcUserSessionField","接口端产品信息","TThostFtdcProductInfoType", "InterfaceProductInfo", &(m_ThostFtdcUserSessionField.InterfaceProductInfo));
	RegField("CThostFtdcUserSessionField","协议信息","TThostFtdcProtocolInfoType", "ProtocolInfo", &(m_ThostFtdcUserSessionField.ProtocolInfo));
	RegField("CThostFtdcUserSessionField","Mac地址","TThostFtdcMacAddressType", "MacAddress", &(m_ThostFtdcUserSessionField.MacAddress));

	RegField("CThostFtdcQueryMaxOrderVolumeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQueryMaxOrderVolumeField.BrokerID));
	RegField("CThostFtdcQueryMaxOrderVolumeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQueryMaxOrderVolumeField.InvestorID));
	RegField("CThostFtdcQueryMaxOrderVolumeField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQueryMaxOrderVolumeField.InstrumentID));
	RegField("CThostFtdcQueryMaxOrderVolumeField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcQueryMaxOrderVolumeField.Direction));
	RegField("CThostFtdcQueryMaxOrderVolumeField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcQueryMaxOrderVolumeField.OffsetFlag));
	RegField("CThostFtdcQueryMaxOrderVolumeField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcQueryMaxOrderVolumeField.HedgeFlag));
	RegField("CThostFtdcQueryMaxOrderVolumeField","最大允许报单数量","TThostFtdcVolumeType", "MaxVolume", &(m_ThostFtdcQueryMaxOrderVolumeField.MaxVolume));

	RegField("CThostFtdcSettlementInfoConfirmField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSettlementInfoConfirmField.BrokerID));
	RegField("CThostFtdcSettlementInfoConfirmField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSettlementInfoConfirmField.InvestorID));
	RegField("CThostFtdcSettlementInfoConfirmField","确认日期","TThostFtdcDateType", "ConfirmDate", &(m_ThostFtdcSettlementInfoConfirmField.ConfirmDate));
	RegField("CThostFtdcSettlementInfoConfirmField","确认时间","TThostFtdcTimeType", "ConfirmTime", &(m_ThostFtdcSettlementInfoConfirmField.ConfirmTime));

	RegField("CThostFtdcSyncDepositField","出入金流水号","TThostFtdcDepositSeqNoType", "DepositSeqNo", &(m_ThostFtdcSyncDepositField.DepositSeqNo));
	RegField("CThostFtdcSyncDepositField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncDepositField.BrokerID));
	RegField("CThostFtdcSyncDepositField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncDepositField.InvestorID));
	RegField("CThostFtdcSyncDepositField","入金金额","TThostFtdcMoneyType", "Deposit", &(m_ThostFtdcSyncDepositField.Deposit));
	RegField("CThostFtdcSyncDepositField","是否强制进行","TThostFtdcBoolType", "IsForce", &(m_ThostFtdcSyncDepositField.IsForce));
	RegField("CThostFtdcSyncDepositField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcSyncDepositField.CurrencyID));

	RegField("CThostFtdcSyncFundMortgageField","货币质押流水号","TThostFtdcDepositSeqNoType", "MortgageSeqNo", &(m_ThostFtdcSyncFundMortgageField.MortgageSeqNo));
	RegField("CThostFtdcSyncFundMortgageField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncFundMortgageField.BrokerID));
	RegField("CThostFtdcSyncFundMortgageField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncFundMortgageField.InvestorID));
	RegField("CThostFtdcSyncFundMortgageField","源币种","TThostFtdcCurrencyIDType", "FromCurrencyID", &(m_ThostFtdcSyncFundMortgageField.FromCurrencyID));
	RegField("CThostFtdcSyncFundMortgageField","质押金额","TThostFtdcMoneyType", "MortgageAmount", &(m_ThostFtdcSyncFundMortgageField.MortgageAmount));
	RegField("CThostFtdcSyncFundMortgageField","目标币种","TThostFtdcCurrencyIDType", "ToCurrencyID", &(m_ThostFtdcSyncFundMortgageField.ToCurrencyID));

	RegField("CThostFtdcBrokerSyncField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerSyncField.BrokerID));

	RegField("CThostFtdcSyncingInvestorField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncingInvestorField.InvestorID));
	RegField("CThostFtdcSyncingInvestorField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingInvestorField.BrokerID));
	RegField("CThostFtdcSyncingInvestorField","投资者分组代码","TThostFtdcInvestorIDType", "InvestorGroupID", &(m_ThostFtdcSyncingInvestorField.InvestorGroupID));
	RegField("CThostFtdcSyncingInvestorField","投资者名称","TThostFtdcPartyNameType", "InvestorName", &(m_ThostFtdcSyncingInvestorField.InvestorName));
	RegField("CThostFtdcSyncingInvestorField","证件类型","TThostFtdcIdCardTypeType", "IdentifiedCardType", &(m_ThostFtdcSyncingInvestorField.IdentifiedCardType));
	RegField("CThostFtdcSyncingInvestorField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcSyncingInvestorField.IdentifiedCardNo));
	RegField("CThostFtdcSyncingInvestorField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcSyncingInvestorField.IsActive));
	RegField("CThostFtdcSyncingInvestorField","联系电话","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcSyncingInvestorField.Telephone));
	RegField("CThostFtdcSyncingInvestorField","通讯地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcSyncingInvestorField.Address));
	RegField("CThostFtdcSyncingInvestorField","开户日期","TThostFtdcDateType", "OpenDate", &(m_ThostFtdcSyncingInvestorField.OpenDate));
	RegField("CThostFtdcSyncingInvestorField","手机","TThostFtdcMobileType", "Mobile", &(m_ThostFtdcSyncingInvestorField.Mobile));
	RegField("CThostFtdcSyncingInvestorField","手续费率模板代码","TThostFtdcInvestorIDType", "CommModelID", &(m_ThostFtdcSyncingInvestorField.CommModelID));
	RegField("CThostFtdcSyncingInvestorField","保证金率模板代码","TThostFtdcInvestorIDType", "MarginModelID", &(m_ThostFtdcSyncingInvestorField.MarginModelID));

	RegField("CThostFtdcSyncingTradingCodeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncingTradingCodeField.InvestorID));
	RegField("CThostFtdcSyncingTradingCodeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingTradingCodeField.BrokerID));
	RegField("CThostFtdcSyncingTradingCodeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcSyncingTradingCodeField.ExchangeID));
	RegField("CThostFtdcSyncingTradingCodeField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcSyncingTradingCodeField.ClientID));
	RegField("CThostFtdcSyncingTradingCodeField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcSyncingTradingCodeField.IsActive));
	RegField("CThostFtdcSyncingTradingCodeField","交易编码类型","TThostFtdcClientIDTypeType", "ClientIDType", &(m_ThostFtdcSyncingTradingCodeField.ClientIDType));

	RegField("CThostFtdcSyncingInvestorGroupField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingInvestorGroupField.BrokerID));
	RegField("CThostFtdcSyncingInvestorGroupField","投资者分组代码","TThostFtdcInvestorIDType", "InvestorGroupID", &(m_ThostFtdcSyncingInvestorGroupField.InvestorGroupID));
	RegField("CThostFtdcSyncingInvestorGroupField","投资者分组名称","TThostFtdcInvestorGroupNameType", "InvestorGroupName", &(m_ThostFtdcSyncingInvestorGroupField.InvestorGroupName));

	RegField("CThostFtdcSyncingTradingAccountField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingTradingAccountField.BrokerID));
	RegField("CThostFtdcSyncingTradingAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcSyncingTradingAccountField.AccountID));
	RegField("CThostFtdcSyncingTradingAccountField","上次质押金额","TThostFtdcMoneyType", "PreMortgage", &(m_ThostFtdcSyncingTradingAccountField.PreMortgage));
	RegField("CThostFtdcSyncingTradingAccountField","上次信用额度","TThostFtdcMoneyType", "PreCredit", &(m_ThostFtdcSyncingTradingAccountField.PreCredit));
	RegField("CThostFtdcSyncingTradingAccountField","上次存款额","TThostFtdcMoneyType", "PreDeposit", &(m_ThostFtdcSyncingTradingAccountField.PreDeposit));
	RegField("CThostFtdcSyncingTradingAccountField","上次结算准备金","TThostFtdcMoneyType", "PreBalance", &(m_ThostFtdcSyncingTradingAccountField.PreBalance));
	RegField("CThostFtdcSyncingTradingAccountField","上次占用的保证金","TThostFtdcMoneyType", "PreMargin", &(m_ThostFtdcSyncingTradingAccountField.PreMargin));
	RegField("CThostFtdcSyncingTradingAccountField","利息基数","TThostFtdcMoneyType", "InterestBase", &(m_ThostFtdcSyncingTradingAccountField.InterestBase));
	RegField("CThostFtdcSyncingTradingAccountField","利息收入","TThostFtdcMoneyType", "Interest", &(m_ThostFtdcSyncingTradingAccountField.Interest));
	RegField("CThostFtdcSyncingTradingAccountField","入金金额","TThostFtdcMoneyType", "Deposit", &(m_ThostFtdcSyncingTradingAccountField.Deposit));
	RegField("CThostFtdcSyncingTradingAccountField","出金金额","TThostFtdcMoneyType", "Withdraw", &(m_ThostFtdcSyncingTradingAccountField.Withdraw));
	RegField("CThostFtdcSyncingTradingAccountField","冻结的保证金","TThostFtdcMoneyType", "FrozenMargin", &(m_ThostFtdcSyncingTradingAccountField.FrozenMargin));
	RegField("CThostFtdcSyncingTradingAccountField","冻结的资金","TThostFtdcMoneyType", "FrozenCash", &(m_ThostFtdcSyncingTradingAccountField.FrozenCash));
	RegField("CThostFtdcSyncingTradingAccountField","冻结的手续费","TThostFtdcMoneyType", "FrozenCommission", &(m_ThostFtdcSyncingTradingAccountField.FrozenCommission));
	RegField("CThostFtdcSyncingTradingAccountField","当前保证金总额","TThostFtdcMoneyType", "CurrMargin", &(m_ThostFtdcSyncingTradingAccountField.CurrMargin));
	RegField("CThostFtdcSyncingTradingAccountField","资金差额","TThostFtdcMoneyType", "CashIn", &(m_ThostFtdcSyncingTradingAccountField.CashIn));
	RegField("CThostFtdcSyncingTradingAccountField","手续费","TThostFtdcMoneyType", "Commission", &(m_ThostFtdcSyncingTradingAccountField.Commission));
	RegField("CThostFtdcSyncingTradingAccountField","平仓盈亏","TThostFtdcMoneyType", "CloseProfit", &(m_ThostFtdcSyncingTradingAccountField.CloseProfit));
	RegField("CThostFtdcSyncingTradingAccountField","持仓盈亏","TThostFtdcMoneyType", "PositionProfit", &(m_ThostFtdcSyncingTradingAccountField.PositionProfit));
	RegField("CThostFtdcSyncingTradingAccountField","期货结算准备金","TThostFtdcMoneyType", "Balance", &(m_ThostFtdcSyncingTradingAccountField.Balance));
	RegField("CThostFtdcSyncingTradingAccountField","可用资金","TThostFtdcMoneyType", "Available", &(m_ThostFtdcSyncingTradingAccountField.Available));
	RegField("CThostFtdcSyncingTradingAccountField","可取资金","TThostFtdcMoneyType", "WithdrawQuota", &(m_ThostFtdcSyncingTradingAccountField.WithdrawQuota));
	RegField("CThostFtdcSyncingTradingAccountField","基本准备金","TThostFtdcMoneyType", "Reserve", &(m_ThostFtdcSyncingTradingAccountField.Reserve));
	RegField("CThostFtdcSyncingTradingAccountField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcSyncingTradingAccountField.TradingDay));
	RegField("CThostFtdcSyncingTradingAccountField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcSyncingTradingAccountField.SettlementID));
	RegField("CThostFtdcSyncingTradingAccountField","信用额度","TThostFtdcMoneyType", "Credit", &(m_ThostFtdcSyncingTradingAccountField.Credit));
	RegField("CThostFtdcSyncingTradingAccountField","质押金额","TThostFtdcMoneyType", "Mortgage", &(m_ThostFtdcSyncingTradingAccountField.Mortgage));
	RegField("CThostFtdcSyncingTradingAccountField","交易所保证金","TThostFtdcMoneyType", "ExchangeMargin", &(m_ThostFtdcSyncingTradingAccountField.ExchangeMargin));
	RegField("CThostFtdcSyncingTradingAccountField","投资者交割保证金","TThostFtdcMoneyType", "DeliveryMargin", &(m_ThostFtdcSyncingTradingAccountField.DeliveryMargin));
	RegField("CThostFtdcSyncingTradingAccountField","交易所交割保证金","TThostFtdcMoneyType", "ExchangeDeliveryMargin", &(m_ThostFtdcSyncingTradingAccountField.ExchangeDeliveryMargin));
	RegField("CThostFtdcSyncingTradingAccountField","保底期货结算准备金","TThostFtdcMoneyType", "ReserveBalance", &(m_ThostFtdcSyncingTradingAccountField.ReserveBalance));
	RegField("CThostFtdcSyncingTradingAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcSyncingTradingAccountField.CurrencyID));
	RegField("CThostFtdcSyncingTradingAccountField","上次货币质入金额","TThostFtdcMoneyType", "PreFundMortgageIn", &(m_ThostFtdcSyncingTradingAccountField.PreFundMortgageIn));
	RegField("CThostFtdcSyncingTradingAccountField","上次货币质出金额","TThostFtdcMoneyType", "PreFundMortgageOut", &(m_ThostFtdcSyncingTradingAccountField.PreFundMortgageOut));
	RegField("CThostFtdcSyncingTradingAccountField","货币质入金额","TThostFtdcMoneyType", "FundMortgageIn", &(m_ThostFtdcSyncingTradingAccountField.FundMortgageIn));
	RegField("CThostFtdcSyncingTradingAccountField","货币质出金额","TThostFtdcMoneyType", "FundMortgageOut", &(m_ThostFtdcSyncingTradingAccountField.FundMortgageOut));
	RegField("CThostFtdcSyncingTradingAccountField","货币质押余额","TThostFtdcMoneyType", "FundMortgageAvailable", &(m_ThostFtdcSyncingTradingAccountField.FundMortgageAvailable));
	RegField("CThostFtdcSyncingTradingAccountField","可质押货币金额","TThostFtdcMoneyType", "MortgageableFund", &(m_ThostFtdcSyncingTradingAccountField.MortgageableFund));
	RegField("CThostFtdcSyncingTradingAccountField","特殊产品占用保证金","TThostFtdcMoneyType", "SpecProductMargin", &(m_ThostFtdcSyncingTradingAccountField.SpecProductMargin));
	RegField("CThostFtdcSyncingTradingAccountField","特殊产品冻结保证金","TThostFtdcMoneyType", "SpecProductFrozenMargin", &(m_ThostFtdcSyncingTradingAccountField.SpecProductFrozenMargin));
	RegField("CThostFtdcSyncingTradingAccountField","特殊产品手续费","TThostFtdcMoneyType", "SpecProductCommission", &(m_ThostFtdcSyncingTradingAccountField.SpecProductCommission));
	RegField("CThostFtdcSyncingTradingAccountField","特殊产品冻结手续费","TThostFtdcMoneyType", "SpecProductFrozenCommission", &(m_ThostFtdcSyncingTradingAccountField.SpecProductFrozenCommission));
	RegField("CThostFtdcSyncingTradingAccountField","特殊产品持仓盈亏","TThostFtdcMoneyType", "SpecProductPositionProfit", &(m_ThostFtdcSyncingTradingAccountField.SpecProductPositionProfit));
	RegField("CThostFtdcSyncingTradingAccountField","特殊产品平仓盈亏","TThostFtdcMoneyType", "SpecProductCloseProfit", &(m_ThostFtdcSyncingTradingAccountField.SpecProductCloseProfit));
	RegField("CThostFtdcSyncingTradingAccountField","根据持仓盈亏算法计算的特殊产品持仓盈亏","TThostFtdcMoneyType", "SpecProductPositionProfitByAlg", &(m_ThostFtdcSyncingTradingAccountField.SpecProductPositionProfitByAlg));
	RegField("CThostFtdcSyncingTradingAccountField","特殊产品交易所保证金","TThostFtdcMoneyType", "SpecProductExchangeMargin", &(m_ThostFtdcSyncingTradingAccountField.SpecProductExchangeMargin));
	RegField("CThostFtdcSyncingTradingAccountField","期权平仓盈亏","TThostFtdcMoneyType", "OptionCloseProfit", &(m_ThostFtdcSyncingTradingAccountField.OptionCloseProfit));
	RegField("CThostFtdcSyncingTradingAccountField","期权市值","TThostFtdcMoneyType", "OptionValue", &(m_ThostFtdcSyncingTradingAccountField.OptionValue));

	RegField("CThostFtdcSyncingInvestorPositionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcSyncingInvestorPositionField.InstrumentID));
	RegField("CThostFtdcSyncingInvestorPositionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingInvestorPositionField.BrokerID));
	RegField("CThostFtdcSyncingInvestorPositionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncingInvestorPositionField.InvestorID));
	RegField("CThostFtdcSyncingInvestorPositionField","持仓多空方向","TThostFtdcPosiDirectionType", "PosiDirection", &(m_ThostFtdcSyncingInvestorPositionField.PosiDirection));
	RegField("CThostFtdcSyncingInvestorPositionField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcSyncingInvestorPositionField.HedgeFlag));
	RegField("CThostFtdcSyncingInvestorPositionField","持仓日期","TThostFtdcPositionDateType", "PositionDate", &(m_ThostFtdcSyncingInvestorPositionField.PositionDate));
	RegField("CThostFtdcSyncingInvestorPositionField","上日持仓","TThostFtdcVolumeType", "YdPosition", &(m_ThostFtdcSyncingInvestorPositionField.YdPosition));
	RegField("CThostFtdcSyncingInvestorPositionField","今日持仓","TThostFtdcVolumeType", "Position", &(m_ThostFtdcSyncingInvestorPositionField.Position));
	RegField("CThostFtdcSyncingInvestorPositionField","多头冻结","TThostFtdcVolumeType", "LongFrozen", &(m_ThostFtdcSyncingInvestorPositionField.LongFrozen));
	RegField("CThostFtdcSyncingInvestorPositionField","空头冻结","TThostFtdcVolumeType", "ShortFrozen", &(m_ThostFtdcSyncingInvestorPositionField.ShortFrozen));
	RegField("CThostFtdcSyncingInvestorPositionField","开仓冻结金额","TThostFtdcMoneyType", "LongFrozenAmount", &(m_ThostFtdcSyncingInvestorPositionField.LongFrozenAmount));
	RegField("CThostFtdcSyncingInvestorPositionField","开仓冻结金额","TThostFtdcMoneyType", "ShortFrozenAmount", &(m_ThostFtdcSyncingInvestorPositionField.ShortFrozenAmount));
	RegField("CThostFtdcSyncingInvestorPositionField","开仓量","TThostFtdcVolumeType", "OpenVolume", &(m_ThostFtdcSyncingInvestorPositionField.OpenVolume));
	RegField("CThostFtdcSyncingInvestorPositionField","平仓量","TThostFtdcVolumeType", "CloseVolume", &(m_ThostFtdcSyncingInvestorPositionField.CloseVolume));
	RegField("CThostFtdcSyncingInvestorPositionField","开仓金额","TThostFtdcMoneyType", "OpenAmount", &(m_ThostFtdcSyncingInvestorPositionField.OpenAmount));
	RegField("CThostFtdcSyncingInvestorPositionField","平仓金额","TThostFtdcMoneyType", "CloseAmount", &(m_ThostFtdcSyncingInvestorPositionField.CloseAmount));
	RegField("CThostFtdcSyncingInvestorPositionField","持仓成本","TThostFtdcMoneyType", "PositionCost", &(m_ThostFtdcSyncingInvestorPositionField.PositionCost));
	RegField("CThostFtdcSyncingInvestorPositionField","上次占用的保证金","TThostFtdcMoneyType", "PreMargin", &(m_ThostFtdcSyncingInvestorPositionField.PreMargin));
	RegField("CThostFtdcSyncingInvestorPositionField","占用的保证金","TThostFtdcMoneyType", "UseMargin", &(m_ThostFtdcSyncingInvestorPositionField.UseMargin));
	RegField("CThostFtdcSyncingInvestorPositionField","冻结的保证金","TThostFtdcMoneyType", "FrozenMargin", &(m_ThostFtdcSyncingInvestorPositionField.FrozenMargin));
	RegField("CThostFtdcSyncingInvestorPositionField","冻结的资金","TThostFtdcMoneyType", "FrozenCash", &(m_ThostFtdcSyncingInvestorPositionField.FrozenCash));
	RegField("CThostFtdcSyncingInvestorPositionField","冻结的手续费","TThostFtdcMoneyType", "FrozenCommission", &(m_ThostFtdcSyncingInvestorPositionField.FrozenCommission));
	RegField("CThostFtdcSyncingInvestorPositionField","资金差额","TThostFtdcMoneyType", "CashIn", &(m_ThostFtdcSyncingInvestorPositionField.CashIn));
	RegField("CThostFtdcSyncingInvestorPositionField","手续费","TThostFtdcMoneyType", "Commission", &(m_ThostFtdcSyncingInvestorPositionField.Commission));
	RegField("CThostFtdcSyncingInvestorPositionField","平仓盈亏","TThostFtdcMoneyType", "CloseProfit", &(m_ThostFtdcSyncingInvestorPositionField.CloseProfit));
	RegField("CThostFtdcSyncingInvestorPositionField","持仓盈亏","TThostFtdcMoneyType", "PositionProfit", &(m_ThostFtdcSyncingInvestorPositionField.PositionProfit));
	RegField("CThostFtdcSyncingInvestorPositionField","上次结算价","TThostFtdcPriceType", "PreSettlementPrice", &(m_ThostFtdcSyncingInvestorPositionField.PreSettlementPrice));
	RegField("CThostFtdcSyncingInvestorPositionField","本次结算价","TThostFtdcPriceType", "SettlementPrice", &(m_ThostFtdcSyncingInvestorPositionField.SettlementPrice));
	RegField("CThostFtdcSyncingInvestorPositionField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcSyncingInvestorPositionField.TradingDay));
	RegField("CThostFtdcSyncingInvestorPositionField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcSyncingInvestorPositionField.SettlementID));
	RegField("CThostFtdcSyncingInvestorPositionField","开仓成本","TThostFtdcMoneyType", "OpenCost", &(m_ThostFtdcSyncingInvestorPositionField.OpenCost));
	RegField("CThostFtdcSyncingInvestorPositionField","交易所保证金","TThostFtdcMoneyType", "ExchangeMargin", &(m_ThostFtdcSyncingInvestorPositionField.ExchangeMargin));
	RegField("CThostFtdcSyncingInvestorPositionField","组合成交形成的持仓","TThostFtdcVolumeType", "CombPosition", &(m_ThostFtdcSyncingInvestorPositionField.CombPosition));
	RegField("CThostFtdcSyncingInvestorPositionField","组合多头冻结","TThostFtdcVolumeType", "CombLongFrozen", &(m_ThostFtdcSyncingInvestorPositionField.CombLongFrozen));
	RegField("CThostFtdcSyncingInvestorPositionField","组合空头冻结","TThostFtdcVolumeType", "CombShortFrozen", &(m_ThostFtdcSyncingInvestorPositionField.CombShortFrozen));
	RegField("CThostFtdcSyncingInvestorPositionField","逐日盯市平仓盈亏","TThostFtdcMoneyType", "CloseProfitByDate", &(m_ThostFtdcSyncingInvestorPositionField.CloseProfitByDate));
	RegField("CThostFtdcSyncingInvestorPositionField","逐笔对冲平仓盈亏","TThostFtdcMoneyType", "CloseProfitByTrade", &(m_ThostFtdcSyncingInvestorPositionField.CloseProfitByTrade));
	RegField("CThostFtdcSyncingInvestorPositionField","今日持仓","TThostFtdcVolumeType", "TodayPosition", &(m_ThostFtdcSyncingInvestorPositionField.TodayPosition));
	RegField("CThostFtdcSyncingInvestorPositionField","保证金率","TThostFtdcRatioType", "MarginRateByMoney", &(m_ThostFtdcSyncingInvestorPositionField.MarginRateByMoney));
	RegField("CThostFtdcSyncingInvestorPositionField","保证金率","TThostFtdcRatioType", "MarginRateByVolume", &(m_ThostFtdcSyncingInvestorPositionField.MarginRateByVolume));
	RegField("CThostFtdcSyncingInvestorPositionField","执行冻结","TThostFtdcVolumeType", "StrikeFrozen", &(m_ThostFtdcSyncingInvestorPositionField.StrikeFrozen));
	RegField("CThostFtdcSyncingInvestorPositionField","执行冻结金额","TThostFtdcMoneyType", "StrikeFrozenAmount", &(m_ThostFtdcSyncingInvestorPositionField.StrikeFrozenAmount));
	RegField("CThostFtdcSyncingInvestorPositionField","放弃执行冻结","TThostFtdcVolumeType", "AbandonFrozen", &(m_ThostFtdcSyncingInvestorPositionField.AbandonFrozen));
	RegField("CThostFtdcSyncingInvestorPositionField","期权市值","TThostFtdcMoneyType", "OptionValue", &(m_ThostFtdcSyncingInvestorPositionField.OptionValue));

	RegField("CThostFtdcSyncingInstrumentMarginRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcSyncingInstrumentMarginRateField.InstrumentID));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcSyncingInstrumentMarginRateField.InvestorRange));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingInstrumentMarginRateField.BrokerID));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncingInstrumentMarginRateField.InvestorID));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcSyncingInstrumentMarginRateField.HedgeFlag));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","多头保证金率","TThostFtdcRatioType", "LongMarginRatioByMoney", &(m_ThostFtdcSyncingInstrumentMarginRateField.LongMarginRatioByMoney));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","多头保证金费","TThostFtdcMoneyType", "LongMarginRatioByVolume", &(m_ThostFtdcSyncingInstrumentMarginRateField.LongMarginRatioByVolume));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","空头保证金率","TThostFtdcRatioType", "ShortMarginRatioByMoney", &(m_ThostFtdcSyncingInstrumentMarginRateField.ShortMarginRatioByMoney));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","空头保证金费","TThostFtdcMoneyType", "ShortMarginRatioByVolume", &(m_ThostFtdcSyncingInstrumentMarginRateField.ShortMarginRatioByVolume));
	RegField("CThostFtdcSyncingInstrumentMarginRateField","是否相对交易所收取","TThostFtdcBoolType", "IsRelative", &(m_ThostFtdcSyncingInstrumentMarginRateField.IsRelative));

	RegField("CThostFtdcSyncingInstrumentCommissionRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcSyncingInstrumentCommissionRateField.InstrumentID));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcSyncingInstrumentCommissionRateField.InvestorRange));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingInstrumentCommissionRateField.BrokerID));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncingInstrumentCommissionRateField.InvestorID));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","开仓手续费率","TThostFtdcRatioType", "OpenRatioByMoney", &(m_ThostFtdcSyncingInstrumentCommissionRateField.OpenRatioByMoney));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","开仓手续费","TThostFtdcRatioType", "OpenRatioByVolume", &(m_ThostFtdcSyncingInstrumentCommissionRateField.OpenRatioByVolume));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","平仓手续费率","TThostFtdcRatioType", "CloseRatioByMoney", &(m_ThostFtdcSyncingInstrumentCommissionRateField.CloseRatioByMoney));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","平仓手续费","TThostFtdcRatioType", "CloseRatioByVolume", &(m_ThostFtdcSyncingInstrumentCommissionRateField.CloseRatioByVolume));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","平今手续费率","TThostFtdcRatioType", "CloseTodayRatioByMoney", &(m_ThostFtdcSyncingInstrumentCommissionRateField.CloseTodayRatioByMoney));
	RegField("CThostFtdcSyncingInstrumentCommissionRateField","平今手续费","TThostFtdcRatioType", "CloseTodayRatioByVolume", &(m_ThostFtdcSyncingInstrumentCommissionRateField.CloseTodayRatioByVolume));

	RegField("CThostFtdcSyncingInstrumentTradingRightField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcSyncingInstrumentTradingRightField.InstrumentID));
	RegField("CThostFtdcSyncingInstrumentTradingRightField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcSyncingInstrumentTradingRightField.InvestorRange));
	RegField("CThostFtdcSyncingInstrumentTradingRightField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSyncingInstrumentTradingRightField.BrokerID));
	RegField("CThostFtdcSyncingInstrumentTradingRightField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcSyncingInstrumentTradingRightField.InvestorID));
	RegField("CThostFtdcSyncingInstrumentTradingRightField","交易权限","TThostFtdcTradingRightType", "TradingRight", &(m_ThostFtdcSyncingInstrumentTradingRightField.TradingRight));

	RegField("CThostFtdcQryOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryOrderField.BrokerID));
	RegField("CThostFtdcQryOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryOrderField.InvestorID));
	RegField("CThostFtdcQryOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryOrderField.InstrumentID));
	RegField("CThostFtdcQryOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryOrderField.ExchangeID));
	RegField("CThostFtdcQryOrderField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcQryOrderField.OrderSysID));
	RegField("CThostFtdcQryOrderField","开始时间","TThostFtdcTimeType", "InsertTimeStart", &(m_ThostFtdcQryOrderField.InsertTimeStart));
	RegField("CThostFtdcQryOrderField","结束时间","TThostFtdcTimeType", "InsertTimeEnd", &(m_ThostFtdcQryOrderField.InsertTimeEnd));

	RegField("CThostFtdcQryTradeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryTradeField.BrokerID));
	RegField("CThostFtdcQryTradeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryTradeField.InvestorID));
	RegField("CThostFtdcQryTradeField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryTradeField.InstrumentID));
	RegField("CThostFtdcQryTradeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryTradeField.ExchangeID));
	RegField("CThostFtdcQryTradeField","成交编号","TThostFtdcTradeIDType", "TradeID", &(m_ThostFtdcQryTradeField.TradeID));
	RegField("CThostFtdcQryTradeField","开始时间","TThostFtdcTimeType", "TradeTimeStart", &(m_ThostFtdcQryTradeField.TradeTimeStart));
	RegField("CThostFtdcQryTradeField","结束时间","TThostFtdcTimeType", "TradeTimeEnd", &(m_ThostFtdcQryTradeField.TradeTimeEnd));

	RegField("CThostFtdcQryInvestorPositionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInvestorPositionField.BrokerID));
	RegField("CThostFtdcQryInvestorPositionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInvestorPositionField.InvestorID));
	RegField("CThostFtdcQryInvestorPositionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryInvestorPositionField.InstrumentID));

	RegField("CThostFtdcQryTradingAccountField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryTradingAccountField.BrokerID));
	RegField("CThostFtdcQryTradingAccountField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryTradingAccountField.InvestorID));
	RegField("CThostFtdcQryTradingAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcQryTradingAccountField.CurrencyID));

	RegField("CThostFtdcQryInvestorField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInvestorField.BrokerID));
	RegField("CThostFtdcQryInvestorField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInvestorField.InvestorID));

	RegField("CThostFtdcQryTradingCodeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryTradingCodeField.BrokerID));
	RegField("CThostFtdcQryTradingCodeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryTradingCodeField.InvestorID));
	RegField("CThostFtdcQryTradingCodeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryTradingCodeField.ExchangeID));
	RegField("CThostFtdcQryTradingCodeField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryTradingCodeField.ClientID));
	RegField("CThostFtdcQryTradingCodeField","交易编码类型","TThostFtdcClientIDTypeType", "ClientIDType", &(m_ThostFtdcQryTradingCodeField.ClientIDType));

	RegField("CThostFtdcQryInvestorGroupField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInvestorGroupField.BrokerID));

	RegField("CThostFtdcQryInstrumentMarginRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInstrumentMarginRateField.BrokerID));
	RegField("CThostFtdcQryInstrumentMarginRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInstrumentMarginRateField.InvestorID));
	RegField("CThostFtdcQryInstrumentMarginRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryInstrumentMarginRateField.InstrumentID));
	RegField("CThostFtdcQryInstrumentMarginRateField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcQryInstrumentMarginRateField.HedgeFlag));

	RegField("CThostFtdcQryInstrumentCommissionRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInstrumentCommissionRateField.BrokerID));
	RegField("CThostFtdcQryInstrumentCommissionRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInstrumentCommissionRateField.InvestorID));
	RegField("CThostFtdcQryInstrumentCommissionRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryInstrumentCommissionRateField.InstrumentID));

	RegField("CThostFtdcQryInstrumentTradingRightField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInstrumentTradingRightField.BrokerID));
	RegField("CThostFtdcQryInstrumentTradingRightField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInstrumentTradingRightField.InvestorID));
	RegField("CThostFtdcQryInstrumentTradingRightField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryInstrumentTradingRightField.InstrumentID));

	RegField("CThostFtdcQryBrokerField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryBrokerField.BrokerID));

	RegField("CThostFtdcQryTraderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryTraderField.ExchangeID));
	RegField("CThostFtdcQryTraderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryTraderField.ParticipantID));
	RegField("CThostFtdcQryTraderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryTraderField.TraderID));

	RegField("CThostFtdcQrySuperUserFunctionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQrySuperUserFunctionField.UserID));

	RegField("CThostFtdcQryUserSessionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcQryUserSessionField.FrontID));
	RegField("CThostFtdcQryUserSessionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcQryUserSessionField.SessionID));
	RegField("CThostFtdcQryUserSessionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryUserSessionField.BrokerID));
	RegField("CThostFtdcQryUserSessionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQryUserSessionField.UserID));

	RegField("CThostFtdcQryPartBrokerField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryPartBrokerField.ExchangeID));
	RegField("CThostFtdcQryPartBrokerField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryPartBrokerField.BrokerID));
	RegField("CThostFtdcQryPartBrokerField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryPartBrokerField.ParticipantID));

	RegField("CThostFtdcQryFrontStatusField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcQryFrontStatusField.FrontID));

	RegField("CThostFtdcQryExchangeOrderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryExchangeOrderField.ParticipantID));
	RegField("CThostFtdcQryExchangeOrderField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryExchangeOrderField.ClientID));
	RegField("CThostFtdcQryExchangeOrderField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcQryExchangeOrderField.ExchangeInstID));
	RegField("CThostFtdcQryExchangeOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeOrderField.ExchangeID));
	RegField("CThostFtdcQryExchangeOrderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryExchangeOrderField.TraderID));

	RegField("CThostFtdcQryOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryOrderActionField.BrokerID));
	RegField("CThostFtdcQryOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryOrderActionField.InvestorID));
	RegField("CThostFtdcQryOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryOrderActionField.ExchangeID));

	RegField("CThostFtdcQryExchangeOrderActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryExchangeOrderActionField.ParticipantID));
	RegField("CThostFtdcQryExchangeOrderActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryExchangeOrderActionField.ClientID));
	RegField("CThostFtdcQryExchangeOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeOrderActionField.ExchangeID));
	RegField("CThostFtdcQryExchangeOrderActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryExchangeOrderActionField.TraderID));

	RegField("CThostFtdcQrySuperUserField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQrySuperUserField.UserID));

	RegField("CThostFtdcQryExchangeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeField.ExchangeID));

	RegField("CThostFtdcQryProductField","产品代码","TThostFtdcInstrumentIDType", "ProductID", &(m_ThostFtdcQryProductField.ProductID));
	RegField("CThostFtdcQryProductField","产品类型","TThostFtdcProductClassType", "ProductClass", &(m_ThostFtdcQryProductField.ProductClass));

	RegField("CThostFtdcQryInstrumentField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryInstrumentField.InstrumentID));
	RegField("CThostFtdcQryInstrumentField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryInstrumentField.ExchangeID));
	RegField("CThostFtdcQryInstrumentField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcQryInstrumentField.ExchangeInstID));
	RegField("CThostFtdcQryInstrumentField","产品代码","TThostFtdcInstrumentIDType", "ProductID", &(m_ThostFtdcQryInstrumentField.ProductID));

	RegField("CThostFtdcQryDepthMarketDataField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryDepthMarketDataField.InstrumentID));

	RegField("CThostFtdcQryBrokerUserField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryBrokerUserField.BrokerID));
	RegField("CThostFtdcQryBrokerUserField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQryBrokerUserField.UserID));

	RegField("CThostFtdcQryBrokerUserFunctionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryBrokerUserFunctionField.BrokerID));
	RegField("CThostFtdcQryBrokerUserFunctionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQryBrokerUserFunctionField.UserID));

	RegField("CThostFtdcQryTraderOfferField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryTraderOfferField.ExchangeID));
	RegField("CThostFtdcQryTraderOfferField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryTraderOfferField.ParticipantID));
	RegField("CThostFtdcQryTraderOfferField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryTraderOfferField.TraderID));

	RegField("CThostFtdcQrySyncDepositField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQrySyncDepositField.BrokerID));
	RegField("CThostFtdcQrySyncDepositField","出入金流水号","TThostFtdcDepositSeqNoType", "DepositSeqNo", &(m_ThostFtdcQrySyncDepositField.DepositSeqNo));

	RegField("CThostFtdcQrySettlementInfoField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQrySettlementInfoField.BrokerID));
	RegField("CThostFtdcQrySettlementInfoField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQrySettlementInfoField.InvestorID));
	RegField("CThostFtdcQrySettlementInfoField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcQrySettlementInfoField.TradingDay));

	RegField("CThostFtdcQryExchangeMarginRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryExchangeMarginRateField.BrokerID));
	RegField("CThostFtdcQryExchangeMarginRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryExchangeMarginRateField.InstrumentID));
	RegField("CThostFtdcQryExchangeMarginRateField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcQryExchangeMarginRateField.HedgeFlag));

	RegField("CThostFtdcQryExchangeMarginRateAdjustField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryExchangeMarginRateAdjustField.BrokerID));
	RegField("CThostFtdcQryExchangeMarginRateAdjustField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryExchangeMarginRateAdjustField.InstrumentID));
	RegField("CThostFtdcQryExchangeMarginRateAdjustField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcQryExchangeMarginRateAdjustField.HedgeFlag));

	RegField("CThostFtdcQryExchangeRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryExchangeRateField.BrokerID));
	RegField("CThostFtdcQryExchangeRateField","源币种","TThostFtdcCurrencyIDType", "FromCurrencyID", &(m_ThostFtdcQryExchangeRateField.FromCurrencyID));
	RegField("CThostFtdcQryExchangeRateField","目标币种","TThostFtdcCurrencyIDType", "ToCurrencyID", &(m_ThostFtdcQryExchangeRateField.ToCurrencyID));

	RegField("CThostFtdcQrySyncFundMortgageField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQrySyncFundMortgageField.BrokerID));
	RegField("CThostFtdcQrySyncFundMortgageField","货币质押流水号","TThostFtdcDepositSeqNoType", "MortgageSeqNo", &(m_ThostFtdcQrySyncFundMortgageField.MortgageSeqNo));

	RegField("CThostFtdcQryHisOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryHisOrderField.BrokerID));
	RegField("CThostFtdcQryHisOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryHisOrderField.InvestorID));
	RegField("CThostFtdcQryHisOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryHisOrderField.InstrumentID));
	RegField("CThostFtdcQryHisOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryHisOrderField.ExchangeID));
	RegField("CThostFtdcQryHisOrderField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcQryHisOrderField.OrderSysID));
	RegField("CThostFtdcQryHisOrderField","开始时间","TThostFtdcTimeType", "InsertTimeStart", &(m_ThostFtdcQryHisOrderField.InsertTimeStart));
	RegField("CThostFtdcQryHisOrderField","结束时间","TThostFtdcTimeType", "InsertTimeEnd", &(m_ThostFtdcQryHisOrderField.InsertTimeEnd));
	RegField("CThostFtdcQryHisOrderField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcQryHisOrderField.TradingDay));
	RegField("CThostFtdcQryHisOrderField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcQryHisOrderField.SettlementID));

	RegField("CThostFtdcOptionInstrMiniMarginField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOptionInstrMiniMarginField.InstrumentID));
	RegField("CThostFtdcOptionInstrMiniMarginField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcOptionInstrMiniMarginField.InvestorRange));
	RegField("CThostFtdcOptionInstrMiniMarginField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOptionInstrMiniMarginField.BrokerID));
	RegField("CThostFtdcOptionInstrMiniMarginField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOptionInstrMiniMarginField.InvestorID));
	RegField("CThostFtdcOptionInstrMiniMarginField","单位（手）期权合约最小保证金","TThostFtdcMoneyType", "MinMargin", &(m_ThostFtdcOptionInstrMiniMarginField.MinMargin));
	RegField("CThostFtdcOptionInstrMiniMarginField","取值方式","TThostFtdcValueMethodType", "ValueMethod", &(m_ThostFtdcOptionInstrMiniMarginField.ValueMethod));
	RegField("CThostFtdcOptionInstrMiniMarginField","是否跟随交易所收取","TThostFtdcBoolType", "IsRelative", &(m_ThostFtdcOptionInstrMiniMarginField.IsRelative));

	RegField("CThostFtdcOptionInstrMarginAdjustField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOptionInstrMarginAdjustField.InstrumentID));
	RegField("CThostFtdcOptionInstrMarginAdjustField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcOptionInstrMarginAdjustField.InvestorRange));
	RegField("CThostFtdcOptionInstrMarginAdjustField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOptionInstrMarginAdjustField.BrokerID));
	RegField("CThostFtdcOptionInstrMarginAdjustField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOptionInstrMarginAdjustField.InvestorID));
	RegField("CThostFtdcOptionInstrMarginAdjustField","投机空头保证金调整系数","TThostFtdcRatioType", "SShortMarginRatioByMoney", &(m_ThostFtdcOptionInstrMarginAdjustField.SShortMarginRatioByMoney));
	RegField("CThostFtdcOptionInstrMarginAdjustField","投机空头保证金调整系数","TThostFtdcMoneyType", "SShortMarginRatioByVolume", &(m_ThostFtdcOptionInstrMarginAdjustField.SShortMarginRatioByVolume));
	RegField("CThostFtdcOptionInstrMarginAdjustField","保值空头保证金调整系数","TThostFtdcRatioType", "HShortMarginRatioByMoney", &(m_ThostFtdcOptionInstrMarginAdjustField.HShortMarginRatioByMoney));
	RegField("CThostFtdcOptionInstrMarginAdjustField","保值空头保证金调整系数","TThostFtdcMoneyType", "HShortMarginRatioByVolume", &(m_ThostFtdcOptionInstrMarginAdjustField.HShortMarginRatioByVolume));
	RegField("CThostFtdcOptionInstrMarginAdjustField","套利空头保证金调整系数","TThostFtdcRatioType", "AShortMarginRatioByMoney", &(m_ThostFtdcOptionInstrMarginAdjustField.AShortMarginRatioByMoney));
	RegField("CThostFtdcOptionInstrMarginAdjustField","套利空头保证金调整系数","TThostFtdcMoneyType", "AShortMarginRatioByVolume", &(m_ThostFtdcOptionInstrMarginAdjustField.AShortMarginRatioByVolume));
	RegField("CThostFtdcOptionInstrMarginAdjustField","是否跟随交易所收取","TThostFtdcBoolType", "IsRelative", &(m_ThostFtdcOptionInstrMarginAdjustField.IsRelative));

	RegField("CThostFtdcOptionInstrCommRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOptionInstrCommRateField.InstrumentID));
	RegField("CThostFtdcOptionInstrCommRateField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcOptionInstrCommRateField.InvestorRange));
	RegField("CThostFtdcOptionInstrCommRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOptionInstrCommRateField.BrokerID));
	RegField("CThostFtdcOptionInstrCommRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOptionInstrCommRateField.InvestorID));
	RegField("CThostFtdcOptionInstrCommRateField","开仓手续费率","TThostFtdcRatioType", "OpenRatioByMoney", &(m_ThostFtdcOptionInstrCommRateField.OpenRatioByMoney));
	RegField("CThostFtdcOptionInstrCommRateField","开仓手续费","TThostFtdcRatioType", "OpenRatioByVolume", &(m_ThostFtdcOptionInstrCommRateField.OpenRatioByVolume));
	RegField("CThostFtdcOptionInstrCommRateField","平仓手续费率","TThostFtdcRatioType", "CloseRatioByMoney", &(m_ThostFtdcOptionInstrCommRateField.CloseRatioByMoney));
	RegField("CThostFtdcOptionInstrCommRateField","平仓手续费","TThostFtdcRatioType", "CloseRatioByVolume", &(m_ThostFtdcOptionInstrCommRateField.CloseRatioByVolume));
	RegField("CThostFtdcOptionInstrCommRateField","平今手续费率","TThostFtdcRatioType", "CloseTodayRatioByMoney", &(m_ThostFtdcOptionInstrCommRateField.CloseTodayRatioByMoney));
	RegField("CThostFtdcOptionInstrCommRateField","平今手续费","TThostFtdcRatioType", "CloseTodayRatioByVolume", &(m_ThostFtdcOptionInstrCommRateField.CloseTodayRatioByVolume));
	RegField("CThostFtdcOptionInstrCommRateField","执行手续费率","TThostFtdcRatioType", "StrikeRatioByMoney", &(m_ThostFtdcOptionInstrCommRateField.StrikeRatioByMoney));
	RegField("CThostFtdcOptionInstrCommRateField","执行手续费","TThostFtdcRatioType", "StrikeRatioByVolume", &(m_ThostFtdcOptionInstrCommRateField.StrikeRatioByVolume));

	RegField("CThostFtdcOptionInstrTradeCostField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOptionInstrTradeCostField.BrokerID));
	RegField("CThostFtdcOptionInstrTradeCostField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOptionInstrTradeCostField.InvestorID));
	RegField("CThostFtdcOptionInstrTradeCostField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOptionInstrTradeCostField.InstrumentID));
	RegField("CThostFtdcOptionInstrTradeCostField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcOptionInstrTradeCostField.HedgeFlag));
	RegField("CThostFtdcOptionInstrTradeCostField","期权合约保证金不变部分","TThostFtdcMoneyType", "FixedMargin", &(m_ThostFtdcOptionInstrTradeCostField.FixedMargin));
	RegField("CThostFtdcOptionInstrTradeCostField","期权合约最小保证金","TThostFtdcMoneyType", "MiniMargin", &(m_ThostFtdcOptionInstrTradeCostField.MiniMargin));
	RegField("CThostFtdcOptionInstrTradeCostField","期权合约权利金","TThostFtdcMoneyType", "Royalty", &(m_ThostFtdcOptionInstrTradeCostField.Royalty));
	RegField("CThostFtdcOptionInstrTradeCostField","交易所期权合约保证金不变部分","TThostFtdcMoneyType", "ExchFixedMargin", &(m_ThostFtdcOptionInstrTradeCostField.ExchFixedMargin));
	RegField("CThostFtdcOptionInstrTradeCostField","交易所期权合约最小保证金","TThostFtdcMoneyType", "ExchMiniMargin", &(m_ThostFtdcOptionInstrTradeCostField.ExchMiniMargin));

	RegField("CThostFtdcQryOptionInstrTradeCostField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryOptionInstrTradeCostField.BrokerID));
	RegField("CThostFtdcQryOptionInstrTradeCostField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryOptionInstrTradeCostField.InvestorID));
	RegField("CThostFtdcQryOptionInstrTradeCostField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryOptionInstrTradeCostField.InstrumentID));
	RegField("CThostFtdcQryOptionInstrTradeCostField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcQryOptionInstrTradeCostField.HedgeFlag));
	RegField("CThostFtdcQryOptionInstrTradeCostField","期权合约报价","TThostFtdcPriceType", "InputPrice", &(m_ThostFtdcQryOptionInstrTradeCostField.InputPrice));
	RegField("CThostFtdcQryOptionInstrTradeCostField","标的价格,填0则用昨结算价","TThostFtdcPriceType", "UnderlyingPrice", &(m_ThostFtdcQryOptionInstrTradeCostField.UnderlyingPrice));

	RegField("CThostFtdcQryOptionInstrCommRateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryOptionInstrCommRateField.BrokerID));
	RegField("CThostFtdcQryOptionInstrCommRateField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryOptionInstrCommRateField.InvestorID));
	RegField("CThostFtdcQryOptionInstrCommRateField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryOptionInstrCommRateField.InstrumentID));

	RegField("CThostFtdcIndexPriceField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcIndexPriceField.BrokerID));
	RegField("CThostFtdcIndexPriceField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcIndexPriceField.InstrumentID));
	RegField("CThostFtdcIndexPriceField","指数现货收盘价","TThostFtdcPriceType", "ClosePrice", &(m_ThostFtdcIndexPriceField.ClosePrice));

	RegField("CThostFtdcInputExecOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInputExecOrderField.BrokerID));
	RegField("CThostFtdcInputExecOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInputExecOrderField.InvestorID));
	RegField("CThostFtdcInputExecOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInputExecOrderField.InstrumentID));
	RegField("CThostFtdcInputExecOrderField","执行宣告引用","TThostFtdcOrderRefType", "ExecOrderRef", &(m_ThostFtdcInputExecOrderField.ExecOrderRef));
	RegField("CThostFtdcInputExecOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcInputExecOrderField.UserID));
	RegField("CThostFtdcInputExecOrderField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcInputExecOrderField.Volume));
	RegField("CThostFtdcInputExecOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcInputExecOrderField.RequestID));
	RegField("CThostFtdcInputExecOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcInputExecOrderField.BusinessUnit));
	RegField("CThostFtdcInputExecOrderField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcInputExecOrderField.OffsetFlag));
	RegField("CThostFtdcInputExecOrderField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcInputExecOrderField.HedgeFlag));
	RegField("CThostFtdcInputExecOrderField","执行类型","TThostFtdcActionTypeType", "ActionType", &(m_ThostFtdcInputExecOrderField.ActionType));
	RegField("CThostFtdcInputExecOrderField","保留头寸申请的持仓方向","TThostFtdcPosiDirectionType", "PosiDirection", &(m_ThostFtdcInputExecOrderField.PosiDirection));
	RegField("CThostFtdcInputExecOrderField","期权行权后是否保留期货头寸的标记","TThostFtdcExecOrderPositionFlagType", "ReservePositionFlag", &(m_ThostFtdcInputExecOrderField.ReservePositionFlag));
	RegField("CThostFtdcInputExecOrderField","期权行权后生成的头寸是否自动平仓","TThostFtdcExecOrderCloseFlagType", "CloseFlag", &(m_ThostFtdcInputExecOrderField.CloseFlag));

	RegField("CThostFtdcInputExecOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInputExecOrderActionField.BrokerID));
	RegField("CThostFtdcInputExecOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInputExecOrderActionField.InvestorID));
	RegField("CThostFtdcInputExecOrderActionField","执行宣告操作引用","TThostFtdcOrderActionRefType", "ExecOrderActionRef", &(m_ThostFtdcInputExecOrderActionField.ExecOrderActionRef));
	RegField("CThostFtdcInputExecOrderActionField","执行宣告引用","TThostFtdcOrderRefType", "ExecOrderRef", &(m_ThostFtdcInputExecOrderActionField.ExecOrderRef));
	RegField("CThostFtdcInputExecOrderActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcInputExecOrderActionField.RequestID));
	RegField("CThostFtdcInputExecOrderActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcInputExecOrderActionField.FrontID));
	RegField("CThostFtdcInputExecOrderActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcInputExecOrderActionField.SessionID));
	RegField("CThostFtdcInputExecOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcInputExecOrderActionField.ExchangeID));
	RegField("CThostFtdcInputExecOrderActionField","执行宣告操作编号","TThostFtdcExecOrderSysIDType", "ExecOrderSysID", &(m_ThostFtdcInputExecOrderActionField.ExecOrderSysID));
	RegField("CThostFtdcInputExecOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcInputExecOrderActionField.ActionFlag));
	RegField("CThostFtdcInputExecOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcInputExecOrderActionField.UserID));
	RegField("CThostFtdcInputExecOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInputExecOrderActionField.InstrumentID));

	RegField("CThostFtdcExecOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcExecOrderField.BrokerID));
	RegField("CThostFtdcExecOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcExecOrderField.InvestorID));
	RegField("CThostFtdcExecOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcExecOrderField.InstrumentID));
	RegField("CThostFtdcExecOrderField","执行宣告引用","TThostFtdcOrderRefType", "ExecOrderRef", &(m_ThostFtdcExecOrderField.ExecOrderRef));
	RegField("CThostFtdcExecOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcExecOrderField.UserID));
	RegField("CThostFtdcExecOrderField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcExecOrderField.Volume));
	RegField("CThostFtdcExecOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcExecOrderField.RequestID));
	RegField("CThostFtdcExecOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExecOrderField.BusinessUnit));
	RegField("CThostFtdcExecOrderField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcExecOrderField.OffsetFlag));
	RegField("CThostFtdcExecOrderField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcExecOrderField.HedgeFlag));
	RegField("CThostFtdcExecOrderField","执行类型","TThostFtdcActionTypeType", "ActionType", &(m_ThostFtdcExecOrderField.ActionType));
	RegField("CThostFtdcExecOrderField","保留头寸申请的持仓方向","TThostFtdcPosiDirectionType", "PosiDirection", &(m_ThostFtdcExecOrderField.PosiDirection));
	RegField("CThostFtdcExecOrderField","期权行权后是否保留期货头寸的标记","TThostFtdcExecOrderPositionFlagType", "ReservePositionFlag", &(m_ThostFtdcExecOrderField.ReservePositionFlag));
	RegField("CThostFtdcExecOrderField","期权行权后生成的头寸是否自动平仓","TThostFtdcExecOrderCloseFlagType", "CloseFlag", &(m_ThostFtdcExecOrderField.CloseFlag));
	RegField("CThostFtdcExecOrderField","本地执行宣告编号","TThostFtdcOrderLocalIDType", "ExecOrderLocalID", &(m_ThostFtdcExecOrderField.ExecOrderLocalID));
	RegField("CThostFtdcExecOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExecOrderField.ExchangeID));
	RegField("CThostFtdcExecOrderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExecOrderField.ParticipantID));
	RegField("CThostFtdcExecOrderField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExecOrderField.ClientID));
	RegField("CThostFtdcExecOrderField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcExecOrderField.ExchangeInstID));
	RegField("CThostFtdcExecOrderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExecOrderField.TraderID));
	RegField("CThostFtdcExecOrderField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExecOrderField.InstallID));
	RegField("CThostFtdcExecOrderField","执行宣告提交状态","TThostFtdcOrderSubmitStatusType", "OrderSubmitStatus", &(m_ThostFtdcExecOrderField.OrderSubmitStatus));
	RegField("CThostFtdcExecOrderField","报单提示序号","TThostFtdcSequenceNoType", "NotifySequence", &(m_ThostFtdcExecOrderField.NotifySequence));
	RegField("CThostFtdcExecOrderField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcExecOrderField.TradingDay));
	RegField("CThostFtdcExecOrderField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcExecOrderField.SettlementID));
	RegField("CThostFtdcExecOrderField","执行宣告编号","TThostFtdcExecOrderSysIDType", "ExecOrderSysID", &(m_ThostFtdcExecOrderField.ExecOrderSysID));
	RegField("CThostFtdcExecOrderField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcExecOrderField.InsertDate));
	RegField("CThostFtdcExecOrderField","插入时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcExecOrderField.InsertTime));
	RegField("CThostFtdcExecOrderField","撤销时间","TThostFtdcTimeType", "CancelTime", &(m_ThostFtdcExecOrderField.CancelTime));
	RegField("CThostFtdcExecOrderField","执行结果","TThostFtdcExecResultType", "ExecResult", &(m_ThostFtdcExecOrderField.ExecResult));
	RegField("CThostFtdcExecOrderField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcExecOrderField.ClearingPartID));
	RegField("CThostFtdcExecOrderField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcExecOrderField.SequenceNo));
	RegField("CThostFtdcExecOrderField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcExecOrderField.FrontID));
	RegField("CThostFtdcExecOrderField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcExecOrderField.SessionID));
	RegField("CThostFtdcExecOrderField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcExecOrderField.UserProductInfo));
	RegField("CThostFtdcExecOrderField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcExecOrderField.StatusMsg));
	RegField("CThostFtdcExecOrderField","操作用户代码","TThostFtdcUserIDType", "ActiveUserID", &(m_ThostFtdcExecOrderField.ActiveUserID));
	RegField("CThostFtdcExecOrderField","经纪公司报单编号","TThostFtdcSequenceNoType", "BrokerExecOrderSeq", &(m_ThostFtdcExecOrderField.BrokerExecOrderSeq));

	RegField("CThostFtdcExecOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcExecOrderActionField.BrokerID));
	RegField("CThostFtdcExecOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcExecOrderActionField.InvestorID));
	RegField("CThostFtdcExecOrderActionField","执行宣告操作引用","TThostFtdcOrderActionRefType", "ExecOrderActionRef", &(m_ThostFtdcExecOrderActionField.ExecOrderActionRef));
	RegField("CThostFtdcExecOrderActionField","执行宣告引用","TThostFtdcOrderRefType", "ExecOrderRef", &(m_ThostFtdcExecOrderActionField.ExecOrderRef));
	RegField("CThostFtdcExecOrderActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcExecOrderActionField.RequestID));
	RegField("CThostFtdcExecOrderActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcExecOrderActionField.FrontID));
	RegField("CThostFtdcExecOrderActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcExecOrderActionField.SessionID));
	RegField("CThostFtdcExecOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExecOrderActionField.ExchangeID));
	RegField("CThostFtdcExecOrderActionField","执行宣告操作编号","TThostFtdcExecOrderSysIDType", "ExecOrderSysID", &(m_ThostFtdcExecOrderActionField.ExecOrderSysID));
	RegField("CThostFtdcExecOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcExecOrderActionField.ActionFlag));
	RegField("CThostFtdcExecOrderActionField","操作日期","TThostFtdcDateType", "ActionDate", &(m_ThostFtdcExecOrderActionField.ActionDate));
	RegField("CThostFtdcExecOrderActionField","操作时间","TThostFtdcTimeType", "ActionTime", &(m_ThostFtdcExecOrderActionField.ActionTime));
	RegField("CThostFtdcExecOrderActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExecOrderActionField.TraderID));
	RegField("CThostFtdcExecOrderActionField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExecOrderActionField.InstallID));
	RegField("CThostFtdcExecOrderActionField","本地执行宣告编号","TThostFtdcOrderLocalIDType", "ExecOrderLocalID", &(m_ThostFtdcExecOrderActionField.ExecOrderLocalID));
	RegField("CThostFtdcExecOrderActionField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcExecOrderActionField.ActionLocalID));
	RegField("CThostFtdcExecOrderActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExecOrderActionField.ParticipantID));
	RegField("CThostFtdcExecOrderActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExecOrderActionField.ClientID));
	RegField("CThostFtdcExecOrderActionField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExecOrderActionField.BusinessUnit));
	RegField("CThostFtdcExecOrderActionField","报单操作状态","TThostFtdcOrderActionStatusType", "OrderActionStatus", &(m_ThostFtdcExecOrderActionField.OrderActionStatus));
	RegField("CThostFtdcExecOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcExecOrderActionField.UserID));
	RegField("CThostFtdcExecOrderActionField","执行类型","TThostFtdcActionTypeType", "ActionType", &(m_ThostFtdcExecOrderActionField.ActionType));
	RegField("CThostFtdcExecOrderActionField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcExecOrderActionField.StatusMsg));
	RegField("CThostFtdcExecOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcExecOrderActionField.InstrumentID));

	RegField("CThostFtdcQryExecOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryExecOrderField.BrokerID));
	RegField("CThostFtdcQryExecOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryExecOrderField.InvestorID));
	RegField("CThostFtdcQryExecOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryExecOrderField.InstrumentID));
	RegField("CThostFtdcQryExecOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExecOrderField.ExchangeID));
	RegField("CThostFtdcQryExecOrderField","执行宣告编号","TThostFtdcExecOrderSysIDType", "ExecOrderSysID", &(m_ThostFtdcQryExecOrderField.ExecOrderSysID));
	RegField("CThostFtdcQryExecOrderField","开始时间","TThostFtdcTimeType", "InsertTimeStart", &(m_ThostFtdcQryExecOrderField.InsertTimeStart));
	RegField("CThostFtdcQryExecOrderField","结束时间","TThostFtdcTimeType", "InsertTimeEnd", &(m_ThostFtdcQryExecOrderField.InsertTimeEnd));

	RegField("CThostFtdcExchangeExecOrderField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcExchangeExecOrderField.Volume));
	RegField("CThostFtdcExchangeExecOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcExchangeExecOrderField.RequestID));
	RegField("CThostFtdcExchangeExecOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExchangeExecOrderField.BusinessUnit));
	RegField("CThostFtdcExchangeExecOrderField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcExchangeExecOrderField.OffsetFlag));
	RegField("CThostFtdcExchangeExecOrderField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcExchangeExecOrderField.HedgeFlag));
	RegField("CThostFtdcExchangeExecOrderField","执行类型","TThostFtdcActionTypeType", "ActionType", &(m_ThostFtdcExchangeExecOrderField.ActionType));
	RegField("CThostFtdcExchangeExecOrderField","保留头寸申请的持仓方向","TThostFtdcPosiDirectionType", "PosiDirection", &(m_ThostFtdcExchangeExecOrderField.PosiDirection));
	RegField("CThostFtdcExchangeExecOrderField","期权行权后是否保留期货头寸的标记","TThostFtdcExecOrderPositionFlagType", "ReservePositionFlag", &(m_ThostFtdcExchangeExecOrderField.ReservePositionFlag));
	RegField("CThostFtdcExchangeExecOrderField","期权行权后生成的头寸是否自动平仓","TThostFtdcExecOrderCloseFlagType", "CloseFlag", &(m_ThostFtdcExchangeExecOrderField.CloseFlag));
	RegField("CThostFtdcExchangeExecOrderField","本地执行宣告编号","TThostFtdcOrderLocalIDType", "ExecOrderLocalID", &(m_ThostFtdcExchangeExecOrderField.ExecOrderLocalID));
	RegField("CThostFtdcExchangeExecOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeExecOrderField.ExchangeID));
	RegField("CThostFtdcExchangeExecOrderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeExecOrderField.ParticipantID));
	RegField("CThostFtdcExchangeExecOrderField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeExecOrderField.ClientID));
	RegField("CThostFtdcExchangeExecOrderField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcExchangeExecOrderField.ExchangeInstID));
	RegField("CThostFtdcExchangeExecOrderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeExecOrderField.TraderID));
	RegField("CThostFtdcExchangeExecOrderField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeExecOrderField.InstallID));
	RegField("CThostFtdcExchangeExecOrderField","执行宣告提交状态","TThostFtdcOrderSubmitStatusType", "OrderSubmitStatus", &(m_ThostFtdcExchangeExecOrderField.OrderSubmitStatus));
	RegField("CThostFtdcExchangeExecOrderField","报单提示序号","TThostFtdcSequenceNoType", "NotifySequence", &(m_ThostFtdcExchangeExecOrderField.NotifySequence));
	RegField("CThostFtdcExchangeExecOrderField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcExchangeExecOrderField.TradingDay));
	RegField("CThostFtdcExchangeExecOrderField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcExchangeExecOrderField.SettlementID));
	RegField("CThostFtdcExchangeExecOrderField","执行宣告编号","TThostFtdcExecOrderSysIDType", "ExecOrderSysID", &(m_ThostFtdcExchangeExecOrderField.ExecOrderSysID));
	RegField("CThostFtdcExchangeExecOrderField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcExchangeExecOrderField.InsertDate));
	RegField("CThostFtdcExchangeExecOrderField","插入时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcExchangeExecOrderField.InsertTime));
	RegField("CThostFtdcExchangeExecOrderField","撤销时间","TThostFtdcTimeType", "CancelTime", &(m_ThostFtdcExchangeExecOrderField.CancelTime));
	RegField("CThostFtdcExchangeExecOrderField","执行结果","TThostFtdcExecResultType", "ExecResult", &(m_ThostFtdcExchangeExecOrderField.ExecResult));
	RegField("CThostFtdcExchangeExecOrderField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcExchangeExecOrderField.ClearingPartID));
	RegField("CThostFtdcExchangeExecOrderField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcExchangeExecOrderField.SequenceNo));

	RegField("CThostFtdcQryExchangeExecOrderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryExchangeExecOrderField.ParticipantID));
	RegField("CThostFtdcQryExchangeExecOrderField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryExchangeExecOrderField.ClientID));
	RegField("CThostFtdcQryExchangeExecOrderField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcQryExchangeExecOrderField.ExchangeInstID));
	RegField("CThostFtdcQryExchangeExecOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeExecOrderField.ExchangeID));
	RegField("CThostFtdcQryExchangeExecOrderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryExchangeExecOrderField.TraderID));

	RegField("CThostFtdcQryExecOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryExecOrderActionField.BrokerID));
	RegField("CThostFtdcQryExecOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryExecOrderActionField.InvestorID));
	RegField("CThostFtdcQryExecOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExecOrderActionField.ExchangeID));

	RegField("CThostFtdcExchangeExecOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeExecOrderActionField.ExchangeID));
	RegField("CThostFtdcExchangeExecOrderActionField","执行宣告操作编号","TThostFtdcExecOrderSysIDType", "ExecOrderSysID", &(m_ThostFtdcExchangeExecOrderActionField.ExecOrderSysID));
	RegField("CThostFtdcExchangeExecOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcExchangeExecOrderActionField.ActionFlag));
	RegField("CThostFtdcExchangeExecOrderActionField","操作日期","TThostFtdcDateType", "ActionDate", &(m_ThostFtdcExchangeExecOrderActionField.ActionDate));
	RegField("CThostFtdcExchangeExecOrderActionField","操作时间","TThostFtdcTimeType", "ActionTime", &(m_ThostFtdcExchangeExecOrderActionField.ActionTime));
	RegField("CThostFtdcExchangeExecOrderActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeExecOrderActionField.TraderID));
	RegField("CThostFtdcExchangeExecOrderActionField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeExecOrderActionField.InstallID));
	RegField("CThostFtdcExchangeExecOrderActionField","本地执行宣告编号","TThostFtdcOrderLocalIDType", "ExecOrderLocalID", &(m_ThostFtdcExchangeExecOrderActionField.ExecOrderLocalID));
	RegField("CThostFtdcExchangeExecOrderActionField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcExchangeExecOrderActionField.ActionLocalID));
	RegField("CThostFtdcExchangeExecOrderActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeExecOrderActionField.ParticipantID));
	RegField("CThostFtdcExchangeExecOrderActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeExecOrderActionField.ClientID));
	RegField("CThostFtdcExchangeExecOrderActionField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExchangeExecOrderActionField.BusinessUnit));
	RegField("CThostFtdcExchangeExecOrderActionField","报单操作状态","TThostFtdcOrderActionStatusType", "OrderActionStatus", &(m_ThostFtdcExchangeExecOrderActionField.OrderActionStatus));
	RegField("CThostFtdcExchangeExecOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcExchangeExecOrderActionField.UserID));
	RegField("CThostFtdcExchangeExecOrderActionField","执行类型","TThostFtdcActionTypeType", "ActionType", &(m_ThostFtdcExchangeExecOrderActionField.ActionType));

	RegField("CThostFtdcQryExchangeExecOrderActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryExchangeExecOrderActionField.ParticipantID));
	RegField("CThostFtdcQryExchangeExecOrderActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryExchangeExecOrderActionField.ClientID));
	RegField("CThostFtdcQryExchangeExecOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeExecOrderActionField.ExchangeID));
	RegField("CThostFtdcQryExchangeExecOrderActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryExchangeExecOrderActionField.TraderID));

	RegField("CThostFtdcErrExecOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcErrExecOrderField.BrokerID));
	RegField("CThostFtdcErrExecOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcErrExecOrderField.InvestorID));
	RegField("CThostFtdcErrExecOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcErrExecOrderField.InstrumentID));
	RegField("CThostFtdcErrExecOrderField","执行宣告引用","TThostFtdcOrderRefType", "ExecOrderRef", &(m_ThostFtdcErrExecOrderField.ExecOrderRef));
	RegField("CThostFtdcErrExecOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcErrExecOrderField.UserID));
	RegField("CThostFtdcErrExecOrderField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcErrExecOrderField.Volume));
	RegField("CThostFtdcErrExecOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcErrExecOrderField.RequestID));
	RegField("CThostFtdcErrExecOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcErrExecOrderField.BusinessUnit));
	RegField("CThostFtdcErrExecOrderField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcErrExecOrderField.OffsetFlag));
	RegField("CThostFtdcErrExecOrderField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcErrExecOrderField.HedgeFlag));
	RegField("CThostFtdcErrExecOrderField","执行类型","TThostFtdcActionTypeType", "ActionType", &(m_ThostFtdcErrExecOrderField.ActionType));
	RegField("CThostFtdcErrExecOrderField","保留头寸申请的持仓方向","TThostFtdcPosiDirectionType", "PosiDirection", &(m_ThostFtdcErrExecOrderField.PosiDirection));
	RegField("CThostFtdcErrExecOrderField","期权行权后是否保留期货头寸的标记","TThostFtdcExecOrderPositionFlagType", "ReservePositionFlag", &(m_ThostFtdcErrExecOrderField.ReservePositionFlag));
	RegField("CThostFtdcErrExecOrderField","期权行权后生成的头寸是否自动平仓","TThostFtdcExecOrderCloseFlagType", "CloseFlag", &(m_ThostFtdcErrExecOrderField.CloseFlag));
	RegField("CThostFtdcErrExecOrderField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcErrExecOrderField.ErrorID));
	RegField("CThostFtdcErrExecOrderField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcErrExecOrderField.ErrorMsg));

	RegField("CThostFtdcQryErrExecOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryErrExecOrderField.BrokerID));
	RegField("CThostFtdcQryErrExecOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryErrExecOrderField.InvestorID));

	RegField("CThostFtdcErrExecOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcErrExecOrderActionField.BrokerID));
	RegField("CThostFtdcErrExecOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcErrExecOrderActionField.InvestorID));
	RegField("CThostFtdcErrExecOrderActionField","执行宣告操作引用","TThostFtdcOrderActionRefType", "ExecOrderActionRef", &(m_ThostFtdcErrExecOrderActionField.ExecOrderActionRef));
	RegField("CThostFtdcErrExecOrderActionField","执行宣告引用","TThostFtdcOrderRefType", "ExecOrderRef", &(m_ThostFtdcErrExecOrderActionField.ExecOrderRef));
	RegField("CThostFtdcErrExecOrderActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcErrExecOrderActionField.RequestID));
	RegField("CThostFtdcErrExecOrderActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcErrExecOrderActionField.FrontID));
	RegField("CThostFtdcErrExecOrderActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcErrExecOrderActionField.SessionID));
	RegField("CThostFtdcErrExecOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcErrExecOrderActionField.ExchangeID));
	RegField("CThostFtdcErrExecOrderActionField","执行宣告操作编号","TThostFtdcExecOrderSysIDType", "ExecOrderSysID", &(m_ThostFtdcErrExecOrderActionField.ExecOrderSysID));
	RegField("CThostFtdcErrExecOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcErrExecOrderActionField.ActionFlag));
	RegField("CThostFtdcErrExecOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcErrExecOrderActionField.UserID));
	RegField("CThostFtdcErrExecOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcErrExecOrderActionField.InstrumentID));
	RegField("CThostFtdcErrExecOrderActionField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcErrExecOrderActionField.ErrorID));
	RegField("CThostFtdcErrExecOrderActionField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcErrExecOrderActionField.ErrorMsg));

	RegField("CThostFtdcQryErrExecOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryErrExecOrderActionField.BrokerID));
	RegField("CThostFtdcQryErrExecOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryErrExecOrderActionField.InvestorID));

	RegField("CThostFtdcOptionInstrTradingRightField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOptionInstrTradingRightField.InstrumentID));
	RegField("CThostFtdcOptionInstrTradingRightField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcOptionInstrTradingRightField.InvestorRange));
	RegField("CThostFtdcOptionInstrTradingRightField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOptionInstrTradingRightField.BrokerID));
	RegField("CThostFtdcOptionInstrTradingRightField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOptionInstrTradingRightField.InvestorID));
	RegField("CThostFtdcOptionInstrTradingRightField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcOptionInstrTradingRightField.Direction));
	RegField("CThostFtdcOptionInstrTradingRightField","交易权限","TThostFtdcTradingRightType", "TradingRight", &(m_ThostFtdcOptionInstrTradingRightField.TradingRight));

	RegField("CThostFtdcQryOptionInstrTradingRightField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryOptionInstrTradingRightField.BrokerID));
	RegField("CThostFtdcQryOptionInstrTradingRightField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryOptionInstrTradingRightField.InvestorID));
	RegField("CThostFtdcQryOptionInstrTradingRightField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryOptionInstrTradingRightField.InstrumentID));
	RegField("CThostFtdcQryOptionInstrTradingRightField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcQryOptionInstrTradingRightField.Direction));

	RegField("CThostFtdcInputForQuoteField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInputForQuoteField.BrokerID));
	RegField("CThostFtdcInputForQuoteField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInputForQuoteField.InvestorID));
	RegField("CThostFtdcInputForQuoteField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInputForQuoteField.InstrumentID));
	RegField("CThostFtdcInputForQuoteField","询价引用","TThostFtdcOrderRefType", "ForQuoteRef", &(m_ThostFtdcInputForQuoteField.ForQuoteRef));
	RegField("CThostFtdcInputForQuoteField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcInputForQuoteField.UserID));

	RegField("CThostFtdcForQuoteField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcForQuoteField.BrokerID));
	RegField("CThostFtdcForQuoteField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcForQuoteField.InvestorID));
	RegField("CThostFtdcForQuoteField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcForQuoteField.InstrumentID));
	RegField("CThostFtdcForQuoteField","询价引用","TThostFtdcOrderRefType", "ForQuoteRef", &(m_ThostFtdcForQuoteField.ForQuoteRef));
	RegField("CThostFtdcForQuoteField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcForQuoteField.UserID));
	RegField("CThostFtdcForQuoteField","本地询价编号","TThostFtdcOrderLocalIDType", "ForQuoteLocalID", &(m_ThostFtdcForQuoteField.ForQuoteLocalID));
	RegField("CThostFtdcForQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcForQuoteField.ExchangeID));
	RegField("CThostFtdcForQuoteField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcForQuoteField.ParticipantID));
	RegField("CThostFtdcForQuoteField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcForQuoteField.ClientID));
	RegField("CThostFtdcForQuoteField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcForQuoteField.ExchangeInstID));
	RegField("CThostFtdcForQuoteField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcForQuoteField.TraderID));
	RegField("CThostFtdcForQuoteField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcForQuoteField.InstallID));
	RegField("CThostFtdcForQuoteField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcForQuoteField.InsertDate));
	RegField("CThostFtdcForQuoteField","插入时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcForQuoteField.InsertTime));
	RegField("CThostFtdcForQuoteField","询价状态","TThostFtdcForQuoteStatusType", "ForQuoteStatus", &(m_ThostFtdcForQuoteField.ForQuoteStatus));
	RegField("CThostFtdcForQuoteField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcForQuoteField.FrontID));
	RegField("CThostFtdcForQuoteField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcForQuoteField.SessionID));
	RegField("CThostFtdcForQuoteField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcForQuoteField.StatusMsg));
	RegField("CThostFtdcForQuoteField","操作用户代码","TThostFtdcUserIDType", "ActiveUserID", &(m_ThostFtdcForQuoteField.ActiveUserID));
	RegField("CThostFtdcForQuoteField","经纪公司询价编号","TThostFtdcSequenceNoType", "BrokerForQutoSeq", &(m_ThostFtdcForQuoteField.BrokerForQutoSeq));

	RegField("CThostFtdcQryForQuoteField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryForQuoteField.BrokerID));
	RegField("CThostFtdcQryForQuoteField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryForQuoteField.InvestorID));
	RegField("CThostFtdcQryForQuoteField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryForQuoteField.InstrumentID));
	RegField("CThostFtdcQryForQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryForQuoteField.ExchangeID));
	RegField("CThostFtdcQryForQuoteField","开始时间","TThostFtdcTimeType", "InsertTimeStart", &(m_ThostFtdcQryForQuoteField.InsertTimeStart));
	RegField("CThostFtdcQryForQuoteField","结束时间","TThostFtdcTimeType", "InsertTimeEnd", &(m_ThostFtdcQryForQuoteField.InsertTimeEnd));

	RegField("CThostFtdcExchangeForQuoteField","本地询价编号","TThostFtdcOrderLocalIDType", "ForQuoteLocalID", &(m_ThostFtdcExchangeForQuoteField.ForQuoteLocalID));
	RegField("CThostFtdcExchangeForQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeForQuoteField.ExchangeID));
	RegField("CThostFtdcExchangeForQuoteField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeForQuoteField.ParticipantID));
	RegField("CThostFtdcExchangeForQuoteField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeForQuoteField.ClientID));
	RegField("CThostFtdcExchangeForQuoteField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcExchangeForQuoteField.ExchangeInstID));
	RegField("CThostFtdcExchangeForQuoteField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeForQuoteField.TraderID));
	RegField("CThostFtdcExchangeForQuoteField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeForQuoteField.InstallID));
	RegField("CThostFtdcExchangeForQuoteField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcExchangeForQuoteField.InsertDate));
	RegField("CThostFtdcExchangeForQuoteField","插入时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcExchangeForQuoteField.InsertTime));
	RegField("CThostFtdcExchangeForQuoteField","询价状态","TThostFtdcForQuoteStatusType", "ForQuoteStatus", &(m_ThostFtdcExchangeForQuoteField.ForQuoteStatus));

	RegField("CThostFtdcQryExchangeForQuoteField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryExchangeForQuoteField.ParticipantID));
	RegField("CThostFtdcQryExchangeForQuoteField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryExchangeForQuoteField.ClientID));
	RegField("CThostFtdcQryExchangeForQuoteField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcQryExchangeForQuoteField.ExchangeInstID));
	RegField("CThostFtdcQryExchangeForQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeForQuoteField.ExchangeID));
	RegField("CThostFtdcQryExchangeForQuoteField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryExchangeForQuoteField.TraderID));

	RegField("CThostFtdcInputQuoteField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInputQuoteField.BrokerID));
	RegField("CThostFtdcInputQuoteField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInputQuoteField.InvestorID));
	RegField("CThostFtdcInputQuoteField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInputQuoteField.InstrumentID));
	RegField("CThostFtdcInputQuoteField","报价引用","TThostFtdcOrderRefType", "QuoteRef", &(m_ThostFtdcInputQuoteField.QuoteRef));
	RegField("CThostFtdcInputQuoteField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcInputQuoteField.UserID));
	RegField("CThostFtdcInputQuoteField","卖价格","TThostFtdcPriceType", "AskPrice", &(m_ThostFtdcInputQuoteField.AskPrice));
	RegField("CThostFtdcInputQuoteField","买价格","TThostFtdcPriceType", "BidPrice", &(m_ThostFtdcInputQuoteField.BidPrice));
	RegField("CThostFtdcInputQuoteField","卖数量","TThostFtdcVolumeType", "AskVolume", &(m_ThostFtdcInputQuoteField.AskVolume));
	RegField("CThostFtdcInputQuoteField","买数量","TThostFtdcVolumeType", "BidVolume", &(m_ThostFtdcInputQuoteField.BidVolume));
	RegField("CThostFtdcInputQuoteField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcInputQuoteField.RequestID));
	RegField("CThostFtdcInputQuoteField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcInputQuoteField.BusinessUnit));
	RegField("CThostFtdcInputQuoteField","卖开平标志","TThostFtdcOffsetFlagType", "AskOffsetFlag", &(m_ThostFtdcInputQuoteField.AskOffsetFlag));
	RegField("CThostFtdcInputQuoteField","买开平标志","TThostFtdcOffsetFlagType", "BidOffsetFlag", &(m_ThostFtdcInputQuoteField.BidOffsetFlag));
	RegField("CThostFtdcInputQuoteField","卖投机套保标志","TThostFtdcHedgeFlagType", "AskHedgeFlag", &(m_ThostFtdcInputQuoteField.AskHedgeFlag));
	RegField("CThostFtdcInputQuoteField","买投机套保标志","TThostFtdcHedgeFlagType", "BidHedgeFlag", &(m_ThostFtdcInputQuoteField.BidHedgeFlag));

	RegField("CThostFtdcInputQuoteActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInputQuoteActionField.BrokerID));
	RegField("CThostFtdcInputQuoteActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInputQuoteActionField.InvestorID));
	RegField("CThostFtdcInputQuoteActionField","报价操作引用","TThostFtdcOrderActionRefType", "QuoteActionRef", &(m_ThostFtdcInputQuoteActionField.QuoteActionRef));
	RegField("CThostFtdcInputQuoteActionField","报价引用","TThostFtdcOrderRefType", "QuoteRef", &(m_ThostFtdcInputQuoteActionField.QuoteRef));
	RegField("CThostFtdcInputQuoteActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcInputQuoteActionField.RequestID));
	RegField("CThostFtdcInputQuoteActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcInputQuoteActionField.FrontID));
	RegField("CThostFtdcInputQuoteActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcInputQuoteActionField.SessionID));
	RegField("CThostFtdcInputQuoteActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcInputQuoteActionField.ExchangeID));
	RegField("CThostFtdcInputQuoteActionField","报价操作编号","TThostFtdcOrderSysIDType", "QuoteSysID", &(m_ThostFtdcInputQuoteActionField.QuoteSysID));
	RegField("CThostFtdcInputQuoteActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcInputQuoteActionField.ActionFlag));
	RegField("CThostFtdcInputQuoteActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcInputQuoteActionField.UserID));
	RegField("CThostFtdcInputQuoteActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInputQuoteActionField.InstrumentID));

	RegField("CThostFtdcQuoteField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQuoteField.BrokerID));
	RegField("CThostFtdcQuoteField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQuoteField.InvestorID));
	RegField("CThostFtdcQuoteField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQuoteField.InstrumentID));
	RegField("CThostFtdcQuoteField","报价引用","TThostFtdcOrderRefType", "QuoteRef", &(m_ThostFtdcQuoteField.QuoteRef));
	RegField("CThostFtdcQuoteField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQuoteField.UserID));
	RegField("CThostFtdcQuoteField","卖价格","TThostFtdcPriceType", "AskPrice", &(m_ThostFtdcQuoteField.AskPrice));
	RegField("CThostFtdcQuoteField","买价格","TThostFtdcPriceType", "BidPrice", &(m_ThostFtdcQuoteField.BidPrice));
	RegField("CThostFtdcQuoteField","卖数量","TThostFtdcVolumeType", "AskVolume", &(m_ThostFtdcQuoteField.AskVolume));
	RegField("CThostFtdcQuoteField","买数量","TThostFtdcVolumeType", "BidVolume", &(m_ThostFtdcQuoteField.BidVolume));
	RegField("CThostFtdcQuoteField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcQuoteField.RequestID));
	RegField("CThostFtdcQuoteField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcQuoteField.BusinessUnit));
	RegField("CThostFtdcQuoteField","卖开平标志","TThostFtdcOffsetFlagType", "AskOffsetFlag", &(m_ThostFtdcQuoteField.AskOffsetFlag));
	RegField("CThostFtdcQuoteField","买开平标志","TThostFtdcOffsetFlagType", "BidOffsetFlag", &(m_ThostFtdcQuoteField.BidOffsetFlag));
	RegField("CThostFtdcQuoteField","卖投机套保标志","TThostFtdcHedgeFlagType", "AskHedgeFlag", &(m_ThostFtdcQuoteField.AskHedgeFlag));
	RegField("CThostFtdcQuoteField","买投机套保标志","TThostFtdcHedgeFlagType", "BidHedgeFlag", &(m_ThostFtdcQuoteField.BidHedgeFlag));
	RegField("CThostFtdcQuoteField","本地报价编号","TThostFtdcOrderLocalIDType", "QuoteLocalID", &(m_ThostFtdcQuoteField.QuoteLocalID));
	RegField("CThostFtdcQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQuoteField.ExchangeID));
	RegField("CThostFtdcQuoteField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQuoteField.ParticipantID));
	RegField("CThostFtdcQuoteField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQuoteField.ClientID));
	RegField("CThostFtdcQuoteField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcQuoteField.ExchangeInstID));
	RegField("CThostFtdcQuoteField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQuoteField.TraderID));
	RegField("CThostFtdcQuoteField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcQuoteField.InstallID));
	RegField("CThostFtdcQuoteField","报价提示序号","TThostFtdcSequenceNoType", "NotifySequence", &(m_ThostFtdcQuoteField.NotifySequence));
	RegField("CThostFtdcQuoteField","报价提交状态","TThostFtdcOrderSubmitStatusType", "OrderSubmitStatus", &(m_ThostFtdcQuoteField.OrderSubmitStatus));
	RegField("CThostFtdcQuoteField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcQuoteField.TradingDay));
	RegField("CThostFtdcQuoteField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcQuoteField.SettlementID));
	RegField("CThostFtdcQuoteField","报价编号","TThostFtdcOrderSysIDType", "QuoteSysID", &(m_ThostFtdcQuoteField.QuoteSysID));
	RegField("CThostFtdcQuoteField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcQuoteField.InsertDate));
	RegField("CThostFtdcQuoteField","插入时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcQuoteField.InsertTime));
	RegField("CThostFtdcQuoteField","撤销时间","TThostFtdcTimeType", "CancelTime", &(m_ThostFtdcQuoteField.CancelTime));
	RegField("CThostFtdcQuoteField","报价状态","TThostFtdcOrderStatusType", "QuoteStatus", &(m_ThostFtdcQuoteField.QuoteStatus));
	RegField("CThostFtdcQuoteField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcQuoteField.ClearingPartID));
	RegField("CThostFtdcQuoteField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcQuoteField.SequenceNo));
	RegField("CThostFtdcQuoteField","卖方报单编号","TThostFtdcOrderSysIDType", "AskOrderSysID", &(m_ThostFtdcQuoteField.AskOrderSysID));
	RegField("CThostFtdcQuoteField","买方报单编号","TThostFtdcOrderSysIDType", "BidOrderSysID", &(m_ThostFtdcQuoteField.BidOrderSysID));
	RegField("CThostFtdcQuoteField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcQuoteField.FrontID));
	RegField("CThostFtdcQuoteField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcQuoteField.SessionID));
	RegField("CThostFtdcQuoteField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcQuoteField.UserProductInfo));
	RegField("CThostFtdcQuoteField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcQuoteField.StatusMsg));
	RegField("CThostFtdcQuoteField","操作用户代码","TThostFtdcUserIDType", "ActiveUserID", &(m_ThostFtdcQuoteField.ActiveUserID));
	RegField("CThostFtdcQuoteField","经纪公司报价编号","TThostFtdcSequenceNoType", "BrokerQuoteSeq", &(m_ThostFtdcQuoteField.BrokerQuoteSeq));

	RegField("CThostFtdcQuoteActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQuoteActionField.BrokerID));
	RegField("CThostFtdcQuoteActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQuoteActionField.InvestorID));
	RegField("CThostFtdcQuoteActionField","报价操作引用","TThostFtdcOrderActionRefType", "QuoteActionRef", &(m_ThostFtdcQuoteActionField.QuoteActionRef));
	RegField("CThostFtdcQuoteActionField","报价引用","TThostFtdcOrderRefType", "QuoteRef", &(m_ThostFtdcQuoteActionField.QuoteRef));
	RegField("CThostFtdcQuoteActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcQuoteActionField.RequestID));
	RegField("CThostFtdcQuoteActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcQuoteActionField.FrontID));
	RegField("CThostFtdcQuoteActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcQuoteActionField.SessionID));
	RegField("CThostFtdcQuoteActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQuoteActionField.ExchangeID));
	RegField("CThostFtdcQuoteActionField","报价操作编号","TThostFtdcOrderSysIDType", "QuoteSysID", &(m_ThostFtdcQuoteActionField.QuoteSysID));
	RegField("CThostFtdcQuoteActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcQuoteActionField.ActionFlag));
	RegField("CThostFtdcQuoteActionField","操作日期","TThostFtdcDateType", "ActionDate", &(m_ThostFtdcQuoteActionField.ActionDate));
	RegField("CThostFtdcQuoteActionField","操作时间","TThostFtdcTimeType", "ActionTime", &(m_ThostFtdcQuoteActionField.ActionTime));
	RegField("CThostFtdcQuoteActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQuoteActionField.TraderID));
	RegField("CThostFtdcQuoteActionField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcQuoteActionField.InstallID));
	RegField("CThostFtdcQuoteActionField","本地报价编号","TThostFtdcOrderLocalIDType", "QuoteLocalID", &(m_ThostFtdcQuoteActionField.QuoteLocalID));
	RegField("CThostFtdcQuoteActionField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcQuoteActionField.ActionLocalID));
	RegField("CThostFtdcQuoteActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQuoteActionField.ParticipantID));
	RegField("CThostFtdcQuoteActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQuoteActionField.ClientID));
	RegField("CThostFtdcQuoteActionField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcQuoteActionField.BusinessUnit));
	RegField("CThostFtdcQuoteActionField","报单操作状态","TThostFtdcOrderActionStatusType", "OrderActionStatus", &(m_ThostFtdcQuoteActionField.OrderActionStatus));
	RegField("CThostFtdcQuoteActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQuoteActionField.UserID));
	RegField("CThostFtdcQuoteActionField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcQuoteActionField.StatusMsg));
	RegField("CThostFtdcQuoteActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQuoteActionField.InstrumentID));

	RegField("CThostFtdcQryQuoteField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryQuoteField.BrokerID));
	RegField("CThostFtdcQryQuoteField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryQuoteField.InvestorID));
	RegField("CThostFtdcQryQuoteField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryQuoteField.InstrumentID));
	RegField("CThostFtdcQryQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryQuoteField.ExchangeID));
	RegField("CThostFtdcQryQuoteField","报价编号","TThostFtdcOrderSysIDType", "QuoteSysID", &(m_ThostFtdcQryQuoteField.QuoteSysID));
	RegField("CThostFtdcQryQuoteField","开始时间","TThostFtdcTimeType", "InsertTimeStart", &(m_ThostFtdcQryQuoteField.InsertTimeStart));
	RegField("CThostFtdcQryQuoteField","结束时间","TThostFtdcTimeType", "InsertTimeEnd", &(m_ThostFtdcQryQuoteField.InsertTimeEnd));

	RegField("CThostFtdcExchangeQuoteField","卖价格","TThostFtdcPriceType", "AskPrice", &(m_ThostFtdcExchangeQuoteField.AskPrice));
	RegField("CThostFtdcExchangeQuoteField","买价格","TThostFtdcPriceType", "BidPrice", &(m_ThostFtdcExchangeQuoteField.BidPrice));
	RegField("CThostFtdcExchangeQuoteField","卖数量","TThostFtdcVolumeType", "AskVolume", &(m_ThostFtdcExchangeQuoteField.AskVolume));
	RegField("CThostFtdcExchangeQuoteField","买数量","TThostFtdcVolumeType", "BidVolume", &(m_ThostFtdcExchangeQuoteField.BidVolume));
	RegField("CThostFtdcExchangeQuoteField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcExchangeQuoteField.RequestID));
	RegField("CThostFtdcExchangeQuoteField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExchangeQuoteField.BusinessUnit));
	RegField("CThostFtdcExchangeQuoteField","卖开平标志","TThostFtdcOffsetFlagType", "AskOffsetFlag", &(m_ThostFtdcExchangeQuoteField.AskOffsetFlag));
	RegField("CThostFtdcExchangeQuoteField","买开平标志","TThostFtdcOffsetFlagType", "BidOffsetFlag", &(m_ThostFtdcExchangeQuoteField.BidOffsetFlag));
	RegField("CThostFtdcExchangeQuoteField","卖投机套保标志","TThostFtdcHedgeFlagType", "AskHedgeFlag", &(m_ThostFtdcExchangeQuoteField.AskHedgeFlag));
	RegField("CThostFtdcExchangeQuoteField","买投机套保标志","TThostFtdcHedgeFlagType", "BidHedgeFlag", &(m_ThostFtdcExchangeQuoteField.BidHedgeFlag));
	RegField("CThostFtdcExchangeQuoteField","本地报价编号","TThostFtdcOrderLocalIDType", "QuoteLocalID", &(m_ThostFtdcExchangeQuoteField.QuoteLocalID));
	RegField("CThostFtdcExchangeQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeQuoteField.ExchangeID));
	RegField("CThostFtdcExchangeQuoteField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeQuoteField.ParticipantID));
	RegField("CThostFtdcExchangeQuoteField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeQuoteField.ClientID));
	RegField("CThostFtdcExchangeQuoteField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcExchangeQuoteField.ExchangeInstID));
	RegField("CThostFtdcExchangeQuoteField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeQuoteField.TraderID));
	RegField("CThostFtdcExchangeQuoteField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeQuoteField.InstallID));
	RegField("CThostFtdcExchangeQuoteField","报价提示序号","TThostFtdcSequenceNoType", "NotifySequence", &(m_ThostFtdcExchangeQuoteField.NotifySequence));
	RegField("CThostFtdcExchangeQuoteField","报价提交状态","TThostFtdcOrderSubmitStatusType", "OrderSubmitStatus", &(m_ThostFtdcExchangeQuoteField.OrderSubmitStatus));
	RegField("CThostFtdcExchangeQuoteField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcExchangeQuoteField.TradingDay));
	RegField("CThostFtdcExchangeQuoteField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcExchangeQuoteField.SettlementID));
	RegField("CThostFtdcExchangeQuoteField","报价编号","TThostFtdcOrderSysIDType", "QuoteSysID", &(m_ThostFtdcExchangeQuoteField.QuoteSysID));
	RegField("CThostFtdcExchangeQuoteField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcExchangeQuoteField.InsertDate));
	RegField("CThostFtdcExchangeQuoteField","插入时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcExchangeQuoteField.InsertTime));
	RegField("CThostFtdcExchangeQuoteField","撤销时间","TThostFtdcTimeType", "CancelTime", &(m_ThostFtdcExchangeQuoteField.CancelTime));
	RegField("CThostFtdcExchangeQuoteField","报价状态","TThostFtdcOrderStatusType", "QuoteStatus", &(m_ThostFtdcExchangeQuoteField.QuoteStatus));
	RegField("CThostFtdcExchangeQuoteField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcExchangeQuoteField.ClearingPartID));
	RegField("CThostFtdcExchangeQuoteField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcExchangeQuoteField.SequenceNo));
	RegField("CThostFtdcExchangeQuoteField","卖方报单编号","TThostFtdcOrderSysIDType", "AskOrderSysID", &(m_ThostFtdcExchangeQuoteField.AskOrderSysID));
	RegField("CThostFtdcExchangeQuoteField","买方报单编号","TThostFtdcOrderSysIDType", "BidOrderSysID", &(m_ThostFtdcExchangeQuoteField.BidOrderSysID));

	RegField("CThostFtdcQryExchangeQuoteField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryExchangeQuoteField.ParticipantID));
	RegField("CThostFtdcQryExchangeQuoteField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryExchangeQuoteField.ClientID));
	RegField("CThostFtdcQryExchangeQuoteField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcQryExchangeQuoteField.ExchangeInstID));
	RegField("CThostFtdcQryExchangeQuoteField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeQuoteField.ExchangeID));
	RegField("CThostFtdcQryExchangeQuoteField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryExchangeQuoteField.TraderID));

	RegField("CThostFtdcQryQuoteActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryQuoteActionField.BrokerID));
	RegField("CThostFtdcQryQuoteActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryQuoteActionField.InvestorID));
	RegField("CThostFtdcQryQuoteActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryQuoteActionField.ExchangeID));

	RegField("CThostFtdcExchangeQuoteActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeQuoteActionField.ExchangeID));
	RegField("CThostFtdcExchangeQuoteActionField","报价操作编号","TThostFtdcOrderSysIDType", "QuoteSysID", &(m_ThostFtdcExchangeQuoteActionField.QuoteSysID));
	RegField("CThostFtdcExchangeQuoteActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcExchangeQuoteActionField.ActionFlag));
	RegField("CThostFtdcExchangeQuoteActionField","操作日期","TThostFtdcDateType", "ActionDate", &(m_ThostFtdcExchangeQuoteActionField.ActionDate));
	RegField("CThostFtdcExchangeQuoteActionField","操作时间","TThostFtdcTimeType", "ActionTime", &(m_ThostFtdcExchangeQuoteActionField.ActionTime));
	RegField("CThostFtdcExchangeQuoteActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcExchangeQuoteActionField.TraderID));
	RegField("CThostFtdcExchangeQuoteActionField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcExchangeQuoteActionField.InstallID));
	RegField("CThostFtdcExchangeQuoteActionField","本地报价编号","TThostFtdcOrderLocalIDType", "QuoteLocalID", &(m_ThostFtdcExchangeQuoteActionField.QuoteLocalID));
	RegField("CThostFtdcExchangeQuoteActionField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcExchangeQuoteActionField.ActionLocalID));
	RegField("CThostFtdcExchangeQuoteActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcExchangeQuoteActionField.ParticipantID));
	RegField("CThostFtdcExchangeQuoteActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcExchangeQuoteActionField.ClientID));
	RegField("CThostFtdcExchangeQuoteActionField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcExchangeQuoteActionField.BusinessUnit));
	RegField("CThostFtdcExchangeQuoteActionField","报单操作状态","TThostFtdcOrderActionStatusType", "OrderActionStatus", &(m_ThostFtdcExchangeQuoteActionField.OrderActionStatus));
	RegField("CThostFtdcExchangeQuoteActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcExchangeQuoteActionField.UserID));

	RegField("CThostFtdcQryExchangeQuoteActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryExchangeQuoteActionField.ParticipantID));
	RegField("CThostFtdcQryExchangeQuoteActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcQryExchangeQuoteActionField.ClientID));
	RegField("CThostFtdcQryExchangeQuoteActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeQuoteActionField.ExchangeID));
	RegField("CThostFtdcQryExchangeQuoteActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryExchangeQuoteActionField.TraderID));

	RegField("CThostFtdcOptionInstrDeltaField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcOptionInstrDeltaField.InstrumentID));
	RegField("CThostFtdcOptionInstrDeltaField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcOptionInstrDeltaField.InvestorRange));
	RegField("CThostFtdcOptionInstrDeltaField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOptionInstrDeltaField.BrokerID));
	RegField("CThostFtdcOptionInstrDeltaField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcOptionInstrDeltaField.InvestorID));
	RegField("CThostFtdcOptionInstrDeltaField","Delta值","TThostFtdcRatioType", "Delta", &(m_ThostFtdcOptionInstrDeltaField.Delta));

	RegField("CThostFtdcForQuoteRspField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcForQuoteRspField.TradingDay));
	RegField("CThostFtdcForQuoteRspField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcForQuoteRspField.InstrumentID));
	RegField("CThostFtdcForQuoteRspField","询价编号","TThostFtdcOrderSysIDType", "ForQuoteSysID", &(m_ThostFtdcForQuoteRspField.ForQuoteSysID));
	RegField("CThostFtdcForQuoteRspField","询价时间","TThostFtdcTimeType", "ForQuoteTime", &(m_ThostFtdcForQuoteRspField.ForQuoteTime));
	RegField("CThostFtdcForQuoteRspField","业务日期","TThostFtdcDateType", "ActionDay", &(m_ThostFtdcForQuoteRspField.ActionDay));

	RegField("CThostFtdcStrikeOffsetField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcStrikeOffsetField.InstrumentID));
	RegField("CThostFtdcStrikeOffsetField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcStrikeOffsetField.InvestorRange));
	RegField("CThostFtdcStrikeOffsetField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcStrikeOffsetField.BrokerID));
	RegField("CThostFtdcStrikeOffsetField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcStrikeOffsetField.InvestorID));
	RegField("CThostFtdcStrikeOffsetField","执行偏移值","TThostFtdcMoneyType", "Offset", &(m_ThostFtdcStrikeOffsetField.Offset));

	RegField("CThostFtdcQryStrikeOffsetField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryStrikeOffsetField.BrokerID));
	RegField("CThostFtdcQryStrikeOffsetField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryStrikeOffsetField.InvestorID));
	RegField("CThostFtdcQryStrikeOffsetField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryStrikeOffsetField.InstrumentID));

	RegField("CThostFtdcMarketDataField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcMarketDataField.TradingDay));
	RegField("CThostFtdcMarketDataField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcMarketDataField.InstrumentID));
	RegField("CThostFtdcMarketDataField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcMarketDataField.ExchangeID));
	RegField("CThostFtdcMarketDataField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcMarketDataField.ExchangeInstID));
	RegField("CThostFtdcMarketDataField","最新价","TThostFtdcPriceType", "LastPrice", &(m_ThostFtdcMarketDataField.LastPrice));
	RegField("CThostFtdcMarketDataField","上次结算价","TThostFtdcPriceType", "PreSettlementPrice", &(m_ThostFtdcMarketDataField.PreSettlementPrice));
	RegField("CThostFtdcMarketDataField","昨收盘","TThostFtdcPriceType", "PreClosePrice", &(m_ThostFtdcMarketDataField.PreClosePrice));
	RegField("CThostFtdcMarketDataField","昨持仓量","TThostFtdcLargeVolumeType", "PreOpenInterest", &(m_ThostFtdcMarketDataField.PreOpenInterest));
	RegField("CThostFtdcMarketDataField","今开盘","TThostFtdcPriceType", "OpenPrice", &(m_ThostFtdcMarketDataField.OpenPrice));
	RegField("CThostFtdcMarketDataField","最高价","TThostFtdcPriceType", "HighestPrice", &(m_ThostFtdcMarketDataField.HighestPrice));
	RegField("CThostFtdcMarketDataField","最低价","TThostFtdcPriceType", "LowestPrice", &(m_ThostFtdcMarketDataField.LowestPrice));
	RegField("CThostFtdcMarketDataField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcMarketDataField.Volume));
	RegField("CThostFtdcMarketDataField","成交金额","TThostFtdcMoneyType", "Turnover", &(m_ThostFtdcMarketDataField.Turnover));
	RegField("CThostFtdcMarketDataField","持仓量","TThostFtdcLargeVolumeType", "OpenInterest", &(m_ThostFtdcMarketDataField.OpenInterest));
	RegField("CThostFtdcMarketDataField","今收盘","TThostFtdcPriceType", "ClosePrice", &(m_ThostFtdcMarketDataField.ClosePrice));
	RegField("CThostFtdcMarketDataField","本次结算价","TThostFtdcPriceType", "SettlementPrice", &(m_ThostFtdcMarketDataField.SettlementPrice));
	RegField("CThostFtdcMarketDataField","涨停板价","TThostFtdcPriceType", "UpperLimitPrice", &(m_ThostFtdcMarketDataField.UpperLimitPrice));
	RegField("CThostFtdcMarketDataField","跌停板价","TThostFtdcPriceType", "LowerLimitPrice", &(m_ThostFtdcMarketDataField.LowerLimitPrice));
	RegField("CThostFtdcMarketDataField","昨虚实度","TThostFtdcRatioType", "PreDelta", &(m_ThostFtdcMarketDataField.PreDelta));
	RegField("CThostFtdcMarketDataField","今虚实度","TThostFtdcRatioType", "CurrDelta", &(m_ThostFtdcMarketDataField.CurrDelta));
	RegField("CThostFtdcMarketDataField","最后修改时间","TThostFtdcTimeType", "UpdateTime", &(m_ThostFtdcMarketDataField.UpdateTime));
	RegField("CThostFtdcMarketDataField","最后修改毫秒","TThostFtdcMillisecType", "UpdateMillisec", &(m_ThostFtdcMarketDataField.UpdateMillisec));
	RegField("CThostFtdcMarketDataField","业务日期","TThostFtdcDateType", "ActionDay", &(m_ThostFtdcMarketDataField.ActionDay));

	RegField("CThostFtdcMarketDataBaseField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcMarketDataBaseField.TradingDay));
	RegField("CThostFtdcMarketDataBaseField","上次结算价","TThostFtdcPriceType", "PreSettlementPrice", &(m_ThostFtdcMarketDataBaseField.PreSettlementPrice));
	RegField("CThostFtdcMarketDataBaseField","昨收盘","TThostFtdcPriceType", "PreClosePrice", &(m_ThostFtdcMarketDataBaseField.PreClosePrice));
	RegField("CThostFtdcMarketDataBaseField","昨持仓量","TThostFtdcLargeVolumeType", "PreOpenInterest", &(m_ThostFtdcMarketDataBaseField.PreOpenInterest));
	RegField("CThostFtdcMarketDataBaseField","昨虚实度","TThostFtdcRatioType", "PreDelta", &(m_ThostFtdcMarketDataBaseField.PreDelta));

	RegField("CThostFtdcMarketDataStaticField","今开盘","TThostFtdcPriceType", "OpenPrice", &(m_ThostFtdcMarketDataStaticField.OpenPrice));
	RegField("CThostFtdcMarketDataStaticField","最高价","TThostFtdcPriceType", "HighestPrice", &(m_ThostFtdcMarketDataStaticField.HighestPrice));
	RegField("CThostFtdcMarketDataStaticField","最低价","TThostFtdcPriceType", "LowestPrice", &(m_ThostFtdcMarketDataStaticField.LowestPrice));
	RegField("CThostFtdcMarketDataStaticField","今收盘","TThostFtdcPriceType", "ClosePrice", &(m_ThostFtdcMarketDataStaticField.ClosePrice));
	RegField("CThostFtdcMarketDataStaticField","涨停板价","TThostFtdcPriceType", "UpperLimitPrice", &(m_ThostFtdcMarketDataStaticField.UpperLimitPrice));
	RegField("CThostFtdcMarketDataStaticField","跌停板价","TThostFtdcPriceType", "LowerLimitPrice", &(m_ThostFtdcMarketDataStaticField.LowerLimitPrice));
	RegField("CThostFtdcMarketDataStaticField","本次结算价","TThostFtdcPriceType", "SettlementPrice", &(m_ThostFtdcMarketDataStaticField.SettlementPrice));
	RegField("CThostFtdcMarketDataStaticField","今虚实度","TThostFtdcRatioType", "CurrDelta", &(m_ThostFtdcMarketDataStaticField.CurrDelta));

	RegField("CThostFtdcMarketDataLastMatchField","最新价","TThostFtdcPriceType", "LastPrice", &(m_ThostFtdcMarketDataLastMatchField.LastPrice));
	RegField("CThostFtdcMarketDataLastMatchField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcMarketDataLastMatchField.Volume));
	RegField("CThostFtdcMarketDataLastMatchField","成交金额","TThostFtdcMoneyType", "Turnover", &(m_ThostFtdcMarketDataLastMatchField.Turnover));
	RegField("CThostFtdcMarketDataLastMatchField","持仓量","TThostFtdcLargeVolumeType", "OpenInterest", &(m_ThostFtdcMarketDataLastMatchField.OpenInterest));

	RegField("CThostFtdcMarketDataBestPriceField","申买价一","TThostFtdcPriceType", "BidPrice1", &(m_ThostFtdcMarketDataBestPriceField.BidPrice1));
	RegField("CThostFtdcMarketDataBestPriceField","申买量一","TThostFtdcVolumeType", "BidVolume1", &(m_ThostFtdcMarketDataBestPriceField.BidVolume1));
	RegField("CThostFtdcMarketDataBestPriceField","申卖价一","TThostFtdcPriceType", "AskPrice1", &(m_ThostFtdcMarketDataBestPriceField.AskPrice1));
	RegField("CThostFtdcMarketDataBestPriceField","申卖量一","TThostFtdcVolumeType", "AskVolume1", &(m_ThostFtdcMarketDataBestPriceField.AskVolume1));

	RegField("CThostFtdcMarketDataBid23Field","申买价二","TThostFtdcPriceType", "BidPrice2", &(m_ThostFtdcMarketDataBid23Field.BidPrice2));
	RegField("CThostFtdcMarketDataBid23Field","申买量二","TThostFtdcVolumeType", "BidVolume2", &(m_ThostFtdcMarketDataBid23Field.BidVolume2));
	RegField("CThostFtdcMarketDataBid23Field","申买价三","TThostFtdcPriceType", "BidPrice3", &(m_ThostFtdcMarketDataBid23Field.BidPrice3));
	RegField("CThostFtdcMarketDataBid23Field","申买量三","TThostFtdcVolumeType", "BidVolume3", &(m_ThostFtdcMarketDataBid23Field.BidVolume3));

	RegField("CThostFtdcMarketDataAsk23Field","申卖价二","TThostFtdcPriceType", "AskPrice2", &(m_ThostFtdcMarketDataAsk23Field.AskPrice2));
	RegField("CThostFtdcMarketDataAsk23Field","申卖量二","TThostFtdcVolumeType", "AskVolume2", &(m_ThostFtdcMarketDataAsk23Field.AskVolume2));
	RegField("CThostFtdcMarketDataAsk23Field","申卖价三","TThostFtdcPriceType", "AskPrice3", &(m_ThostFtdcMarketDataAsk23Field.AskPrice3));
	RegField("CThostFtdcMarketDataAsk23Field","申卖量三","TThostFtdcVolumeType", "AskVolume3", &(m_ThostFtdcMarketDataAsk23Field.AskVolume3));

	RegField("CThostFtdcMarketDataBid45Field","申买价四","TThostFtdcPriceType", "BidPrice4", &(m_ThostFtdcMarketDataBid45Field.BidPrice4));
	RegField("CThostFtdcMarketDataBid45Field","申买量四","TThostFtdcVolumeType", "BidVolume4", &(m_ThostFtdcMarketDataBid45Field.BidVolume4));
	RegField("CThostFtdcMarketDataBid45Field","申买价五","TThostFtdcPriceType", "BidPrice5", &(m_ThostFtdcMarketDataBid45Field.BidPrice5));
	RegField("CThostFtdcMarketDataBid45Field","申买量五","TThostFtdcVolumeType", "BidVolume5", &(m_ThostFtdcMarketDataBid45Field.BidVolume5));

	RegField("CThostFtdcMarketDataAsk45Field","申卖价四","TThostFtdcPriceType", "AskPrice4", &(m_ThostFtdcMarketDataAsk45Field.AskPrice4));
	RegField("CThostFtdcMarketDataAsk45Field","申卖量四","TThostFtdcVolumeType", "AskVolume4", &(m_ThostFtdcMarketDataAsk45Field.AskVolume4));
	RegField("CThostFtdcMarketDataAsk45Field","申卖价五","TThostFtdcPriceType", "AskPrice5", &(m_ThostFtdcMarketDataAsk45Field.AskPrice5));
	RegField("CThostFtdcMarketDataAsk45Field","申卖量五","TThostFtdcVolumeType", "AskVolume5", &(m_ThostFtdcMarketDataAsk45Field.AskVolume5));

	RegField("CThostFtdcMarketDataUpdateTimeField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcMarketDataUpdateTimeField.InstrumentID));
	RegField("CThostFtdcMarketDataUpdateTimeField","最后修改时间","TThostFtdcTimeType", "UpdateTime", &(m_ThostFtdcMarketDataUpdateTimeField.UpdateTime));
	RegField("CThostFtdcMarketDataUpdateTimeField","最后修改毫秒","TThostFtdcMillisecType", "UpdateMillisec", &(m_ThostFtdcMarketDataUpdateTimeField.UpdateMillisec));
	RegField("CThostFtdcMarketDataUpdateTimeField","业务日期","TThostFtdcDateType", "ActionDay", &(m_ThostFtdcMarketDataUpdateTimeField.ActionDay));

	RegField("CThostFtdcMarketDataExchangeField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcMarketDataExchangeField.ExchangeID));

	RegField("CThostFtdcSpecificInstrumentField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcSpecificInstrumentField.InstrumentID));

	RegField("CThostFtdcInstrumentStatusField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcInstrumentStatusField.ExchangeID));
	RegField("CThostFtdcInstrumentStatusField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcInstrumentStatusField.ExchangeInstID));
	RegField("CThostFtdcInstrumentStatusField","结算组代码","TThostFtdcSettlementGroupIDType", "SettlementGroupID", &(m_ThostFtdcInstrumentStatusField.SettlementGroupID));
	RegField("CThostFtdcInstrumentStatusField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInstrumentStatusField.InstrumentID));
	RegField("CThostFtdcInstrumentStatusField","合约交易状态","TThostFtdcInstrumentStatusType", "InstrumentStatus", &(m_ThostFtdcInstrumentStatusField.InstrumentStatus));
	RegField("CThostFtdcInstrumentStatusField","交易阶段编号","TThostFtdcTradingSegmentSNType", "TradingSegmentSN", &(m_ThostFtdcInstrumentStatusField.TradingSegmentSN));
	RegField("CThostFtdcInstrumentStatusField","进入本状态时间","TThostFtdcTimeType", "EnterTime", &(m_ThostFtdcInstrumentStatusField.EnterTime));
	RegField("CThostFtdcInstrumentStatusField","进入本状态原因","TThostFtdcInstStatusEnterReasonType", "EnterReason", &(m_ThostFtdcInstrumentStatusField.EnterReason));

	RegField("CThostFtdcQryInstrumentStatusField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryInstrumentStatusField.ExchangeID));
	RegField("CThostFtdcQryInstrumentStatusField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcQryInstrumentStatusField.ExchangeInstID));

	RegField("CThostFtdcInvestorAccountField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorAccountField.BrokerID));
	RegField("CThostFtdcInvestorAccountField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInvestorAccountField.InvestorID));
	RegField("CThostFtdcInvestorAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcInvestorAccountField.AccountID));
	RegField("CThostFtdcInvestorAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcInvestorAccountField.CurrencyID));

	RegField("CThostFtdcPositionProfitAlgorithmField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcPositionProfitAlgorithmField.BrokerID));
	RegField("CThostFtdcPositionProfitAlgorithmField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcPositionProfitAlgorithmField.AccountID));
	RegField("CThostFtdcPositionProfitAlgorithmField","盈亏算法","TThostFtdcAlgorithmType", "Algorithm", &(m_ThostFtdcPositionProfitAlgorithmField.Algorithm));
	RegField("CThostFtdcPositionProfitAlgorithmField","备注","TThostFtdcMemoType", "Memo", &(m_ThostFtdcPositionProfitAlgorithmField.Memo));
	RegField("CThostFtdcPositionProfitAlgorithmField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcPositionProfitAlgorithmField.CurrencyID));

	RegField("CThostFtdcDiscountField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcDiscountField.BrokerID));
	RegField("CThostFtdcDiscountField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcDiscountField.InvestorRange));
	RegField("CThostFtdcDiscountField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcDiscountField.InvestorID));
	RegField("CThostFtdcDiscountField","资金折扣比例","TThostFtdcRatioType", "Discount", &(m_ThostFtdcDiscountField.Discount));

	RegField("CThostFtdcQryTransferBankField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcQryTransferBankField.BankID));
	RegField("CThostFtdcQryTransferBankField","银行分中心代码","TThostFtdcBankBrchIDType", "BankBrchID", &(m_ThostFtdcQryTransferBankField.BankBrchID));

	RegField("CThostFtdcTransferBankField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcTransferBankField.BankID));
	RegField("CThostFtdcTransferBankField","银行分中心代码","TThostFtdcBankBrchIDType", "BankBrchID", &(m_ThostFtdcTransferBankField.BankBrchID));
	RegField("CThostFtdcTransferBankField","银行名称","TThostFtdcBankNameType", "BankName", &(m_ThostFtdcTransferBankField.BankName));
	RegField("CThostFtdcTransferBankField","是否活跃","TThostFtdcBoolType", "IsActive", &(m_ThostFtdcTransferBankField.IsActive));

	RegField("CThostFtdcQryInvestorPositionDetailField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInvestorPositionDetailField.BrokerID));
	RegField("CThostFtdcQryInvestorPositionDetailField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInvestorPositionDetailField.InvestorID));
	RegField("CThostFtdcQryInvestorPositionDetailField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryInvestorPositionDetailField.InstrumentID));

	RegField("CThostFtdcInvestorPositionDetailField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInvestorPositionDetailField.InstrumentID));
	RegField("CThostFtdcInvestorPositionDetailField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorPositionDetailField.BrokerID));
	RegField("CThostFtdcInvestorPositionDetailField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInvestorPositionDetailField.InvestorID));
	RegField("CThostFtdcInvestorPositionDetailField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcInvestorPositionDetailField.HedgeFlag));
	RegField("CThostFtdcInvestorPositionDetailField","买卖","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcInvestorPositionDetailField.Direction));
	RegField("CThostFtdcInvestorPositionDetailField","开仓日期","TThostFtdcDateType", "OpenDate", &(m_ThostFtdcInvestorPositionDetailField.OpenDate));
	RegField("CThostFtdcInvestorPositionDetailField","成交编号","TThostFtdcTradeIDType", "TradeID", &(m_ThostFtdcInvestorPositionDetailField.TradeID));
	RegField("CThostFtdcInvestorPositionDetailField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcInvestorPositionDetailField.Volume));
	RegField("CThostFtdcInvestorPositionDetailField","开仓价","TThostFtdcPriceType", "OpenPrice", &(m_ThostFtdcInvestorPositionDetailField.OpenPrice));
	RegField("CThostFtdcInvestorPositionDetailField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcInvestorPositionDetailField.TradingDay));
	RegField("CThostFtdcInvestorPositionDetailField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcInvestorPositionDetailField.SettlementID));
	RegField("CThostFtdcInvestorPositionDetailField","成交类型","TThostFtdcTradeTypeType", "TradeType", &(m_ThostFtdcInvestorPositionDetailField.TradeType));
	RegField("CThostFtdcInvestorPositionDetailField","组合合约代码","TThostFtdcInstrumentIDType", "CombInstrumentID", &(m_ThostFtdcInvestorPositionDetailField.CombInstrumentID));
	RegField("CThostFtdcInvestorPositionDetailField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcInvestorPositionDetailField.ExchangeID));
	RegField("CThostFtdcInvestorPositionDetailField","逐日盯市平仓盈亏","TThostFtdcMoneyType", "CloseProfitByDate", &(m_ThostFtdcInvestorPositionDetailField.CloseProfitByDate));
	RegField("CThostFtdcInvestorPositionDetailField","逐笔对冲平仓盈亏","TThostFtdcMoneyType", "CloseProfitByTrade", &(m_ThostFtdcInvestorPositionDetailField.CloseProfitByTrade));
	RegField("CThostFtdcInvestorPositionDetailField","逐日盯市持仓盈亏","TThostFtdcMoneyType", "PositionProfitByDate", &(m_ThostFtdcInvestorPositionDetailField.PositionProfitByDate));
	RegField("CThostFtdcInvestorPositionDetailField","逐笔对冲持仓盈亏","TThostFtdcMoneyType", "PositionProfitByTrade", &(m_ThostFtdcInvestorPositionDetailField.PositionProfitByTrade));
	RegField("CThostFtdcInvestorPositionDetailField","投资者保证金","TThostFtdcMoneyType", "Margin", &(m_ThostFtdcInvestorPositionDetailField.Margin));
	RegField("CThostFtdcInvestorPositionDetailField","交易所保证金","TThostFtdcMoneyType", "ExchMargin", &(m_ThostFtdcInvestorPositionDetailField.ExchMargin));
	RegField("CThostFtdcInvestorPositionDetailField","保证金率","TThostFtdcRatioType", "MarginRateByMoney", &(m_ThostFtdcInvestorPositionDetailField.MarginRateByMoney));
	RegField("CThostFtdcInvestorPositionDetailField","保证金率","TThostFtdcRatioType", "MarginRateByVolume", &(m_ThostFtdcInvestorPositionDetailField.MarginRateByVolume));
	RegField("CThostFtdcInvestorPositionDetailField","昨结算价","TThostFtdcPriceType", "LastSettlementPrice", &(m_ThostFtdcInvestorPositionDetailField.LastSettlementPrice));
	RegField("CThostFtdcInvestorPositionDetailField","结算价","TThostFtdcPriceType", "SettlementPrice", &(m_ThostFtdcInvestorPositionDetailField.SettlementPrice));
	RegField("CThostFtdcInvestorPositionDetailField","平仓量","TThostFtdcVolumeType", "CloseVolume", &(m_ThostFtdcInvestorPositionDetailField.CloseVolume));
	RegField("CThostFtdcInvestorPositionDetailField","平仓金额","TThostFtdcMoneyType", "CloseAmount", &(m_ThostFtdcInvestorPositionDetailField.CloseAmount));

	RegField("CThostFtdcTradingAccountPasswordField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingAccountPasswordField.BrokerID));
	RegField("CThostFtdcTradingAccountPasswordField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcTradingAccountPasswordField.AccountID));
	RegField("CThostFtdcTradingAccountPasswordField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcTradingAccountPasswordField.Password));
	RegField("CThostFtdcTradingAccountPasswordField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcTradingAccountPasswordField.CurrencyID));

	RegField("CThostFtdcMDTraderOfferField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcMDTraderOfferField.ExchangeID));
	RegField("CThostFtdcMDTraderOfferField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcMDTraderOfferField.TraderID));
	RegField("CThostFtdcMDTraderOfferField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcMDTraderOfferField.ParticipantID));
	RegField("CThostFtdcMDTraderOfferField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcMDTraderOfferField.Password));
	RegField("CThostFtdcMDTraderOfferField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcMDTraderOfferField.InstallID));
	RegField("CThostFtdcMDTraderOfferField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcMDTraderOfferField.OrderLocalID));
	RegField("CThostFtdcMDTraderOfferField","交易所交易员连接状态","TThostFtdcTraderConnectStatusType", "TraderConnectStatus", &(m_ThostFtdcMDTraderOfferField.TraderConnectStatus));
	RegField("CThostFtdcMDTraderOfferField","发出连接请求的日期","TThostFtdcDateType", "ConnectRequestDate", &(m_ThostFtdcMDTraderOfferField.ConnectRequestDate));
	RegField("CThostFtdcMDTraderOfferField","发出连接请求的时间","TThostFtdcTimeType", "ConnectRequestTime", &(m_ThostFtdcMDTraderOfferField.ConnectRequestTime));
	RegField("CThostFtdcMDTraderOfferField","上次报告日期","TThostFtdcDateType", "LastReportDate", &(m_ThostFtdcMDTraderOfferField.LastReportDate));
	RegField("CThostFtdcMDTraderOfferField","上次报告时间","TThostFtdcTimeType", "LastReportTime", &(m_ThostFtdcMDTraderOfferField.LastReportTime));
	RegField("CThostFtdcMDTraderOfferField","完成连接日期","TThostFtdcDateType", "ConnectDate", &(m_ThostFtdcMDTraderOfferField.ConnectDate));
	RegField("CThostFtdcMDTraderOfferField","完成连接时间","TThostFtdcTimeType", "ConnectTime", &(m_ThostFtdcMDTraderOfferField.ConnectTime));
	RegField("CThostFtdcMDTraderOfferField","启动日期","TThostFtdcDateType", "StartDate", &(m_ThostFtdcMDTraderOfferField.StartDate));
	RegField("CThostFtdcMDTraderOfferField","启动时间","TThostFtdcTimeType", "StartTime", &(m_ThostFtdcMDTraderOfferField.StartTime));
	RegField("CThostFtdcMDTraderOfferField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcMDTraderOfferField.TradingDay));
	RegField("CThostFtdcMDTraderOfferField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcMDTraderOfferField.BrokerID));
	RegField("CThostFtdcMDTraderOfferField","本席位最大成交编号","TThostFtdcTradeIDType", "MaxTradeID", &(m_ThostFtdcMDTraderOfferField.MaxTradeID));
	RegField("CThostFtdcMDTraderOfferField","本席位最大报单备拷","TThostFtdcReturnCodeType", "MaxOrderMessageReference", &(m_ThostFtdcMDTraderOfferField.MaxOrderMessageReference));

	RegField("CThostFtdcQryMDTraderOfferField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryMDTraderOfferField.ExchangeID));
	RegField("CThostFtdcQryMDTraderOfferField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcQryMDTraderOfferField.ParticipantID));
	RegField("CThostFtdcQryMDTraderOfferField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcQryMDTraderOfferField.TraderID));

	RegField("CThostFtdcQryNoticeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryNoticeField.BrokerID));

	RegField("CThostFtdcNoticeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcNoticeField.BrokerID));
	RegField("CThostFtdcNoticeField","消息正文","TThostFtdcContentType", "Content", &(m_ThostFtdcNoticeField.Content));
	RegField("CThostFtdcNoticeField","经纪公司通知内容序列号","TThostFtdcSequenceLabelType", "SequenceLabel", &(m_ThostFtdcNoticeField.SequenceLabel));

	RegField("CThostFtdcUserRightField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcUserRightField.BrokerID));
	RegField("CThostFtdcUserRightField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcUserRightField.UserID));
	RegField("CThostFtdcUserRightField","客户权限类型","TThostFtdcUserRightTypeType", "UserRightType", &(m_ThostFtdcUserRightField.UserRightType));
	RegField("CThostFtdcUserRightField","是否禁止","TThostFtdcBoolType", "IsForbidden", &(m_ThostFtdcUserRightField.IsForbidden));

	RegField("CThostFtdcQrySettlementInfoConfirmField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQrySettlementInfoConfirmField.BrokerID));
	RegField("CThostFtdcQrySettlementInfoConfirmField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQrySettlementInfoConfirmField.InvestorID));

	RegField("CThostFtdcLoadSettlementInfoField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcLoadSettlementInfoField.BrokerID));

	RegField("CThostFtdcBrokerWithdrawAlgorithmField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerWithdrawAlgorithmField.BrokerID));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","可提资金算法","TThostFtdcAlgorithmType", "WithdrawAlgorithm", &(m_ThostFtdcBrokerWithdrawAlgorithmField.WithdrawAlgorithm));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","资金使用率","TThostFtdcRatioType", "UsingRatio", &(m_ThostFtdcBrokerWithdrawAlgorithmField.UsingRatio));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","可提是否包含平仓盈利","TThostFtdcIncludeCloseProfitType", "IncludeCloseProfit", &(m_ThostFtdcBrokerWithdrawAlgorithmField.IncludeCloseProfit));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","本日无仓且无成交客户是否受可提比例限制","TThostFtdcAllWithoutTradeType", "AllWithoutTrade", &(m_ThostFtdcBrokerWithdrawAlgorithmField.AllWithoutTrade));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","可用是否包含平仓盈利","TThostFtdcIncludeCloseProfitType", "AvailIncludeCloseProfit", &(m_ThostFtdcBrokerWithdrawAlgorithmField.AvailIncludeCloseProfit));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","是否启用用户事件","TThostFtdcBoolType", "IsBrokerUserEvent", &(m_ThostFtdcBrokerWithdrawAlgorithmField.IsBrokerUserEvent));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcBrokerWithdrawAlgorithmField.CurrencyID));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","货币质押比率","TThostFtdcRatioType", "FundMortgageRatio", &(m_ThostFtdcBrokerWithdrawAlgorithmField.FundMortgageRatio));
	RegField("CThostFtdcBrokerWithdrawAlgorithmField","权益算法","TThostFtdcBalanceAlgorithmType", "BalanceAlgorithm", &(m_ThostFtdcBrokerWithdrawAlgorithmField.BalanceAlgorithm));

	RegField("CThostFtdcTradingAccountPasswordUpdateV1Field","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingAccountPasswordUpdateV1Field.BrokerID));
	RegField("CThostFtdcTradingAccountPasswordUpdateV1Field","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcTradingAccountPasswordUpdateV1Field.InvestorID));
	RegField("CThostFtdcTradingAccountPasswordUpdateV1Field","原来的口令","TThostFtdcPasswordType", "OldPassword", &(m_ThostFtdcTradingAccountPasswordUpdateV1Field.OldPassword));
	RegField("CThostFtdcTradingAccountPasswordUpdateV1Field","新的口令","TThostFtdcPasswordType", "NewPassword", &(m_ThostFtdcTradingAccountPasswordUpdateV1Field.NewPassword));

	RegField("CThostFtdcTradingAccountPasswordUpdateField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingAccountPasswordUpdateField.BrokerID));
	RegField("CThostFtdcTradingAccountPasswordUpdateField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcTradingAccountPasswordUpdateField.AccountID));
	RegField("CThostFtdcTradingAccountPasswordUpdateField","原来的口令","TThostFtdcPasswordType", "OldPassword", &(m_ThostFtdcTradingAccountPasswordUpdateField.OldPassword));
	RegField("CThostFtdcTradingAccountPasswordUpdateField","新的口令","TThostFtdcPasswordType", "NewPassword", &(m_ThostFtdcTradingAccountPasswordUpdateField.NewPassword));
	RegField("CThostFtdcTradingAccountPasswordUpdateField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcTradingAccountPasswordUpdateField.CurrencyID));

	RegField("CThostFtdcQryCombinationLegField","组合合约代码","TThostFtdcInstrumentIDType", "CombInstrumentID", &(m_ThostFtdcQryCombinationLegField.CombInstrumentID));
	RegField("CThostFtdcQryCombinationLegField","单腿编号","TThostFtdcLegIDType", "LegID", &(m_ThostFtdcQryCombinationLegField.LegID));
	RegField("CThostFtdcQryCombinationLegField","单腿合约代码","TThostFtdcInstrumentIDType", "LegInstrumentID", &(m_ThostFtdcQryCombinationLegField.LegInstrumentID));

	RegField("CThostFtdcQrySyncStatusField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcQrySyncStatusField.TradingDay));

	RegField("CThostFtdcCombinationLegField","组合合约代码","TThostFtdcInstrumentIDType", "CombInstrumentID", &(m_ThostFtdcCombinationLegField.CombInstrumentID));
	RegField("CThostFtdcCombinationLegField","单腿编号","TThostFtdcLegIDType", "LegID", &(m_ThostFtdcCombinationLegField.LegID));
	RegField("CThostFtdcCombinationLegField","单腿合约代码","TThostFtdcInstrumentIDType", "LegInstrumentID", &(m_ThostFtdcCombinationLegField.LegInstrumentID));
	RegField("CThostFtdcCombinationLegField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcCombinationLegField.Direction));
	RegField("CThostFtdcCombinationLegField","单腿乘数","TThostFtdcLegMultipleType", "LegMultiple", &(m_ThostFtdcCombinationLegField.LegMultiple));
	RegField("CThostFtdcCombinationLegField","派生层数","TThostFtdcImplyLevelType", "ImplyLevel", &(m_ThostFtdcCombinationLegField.ImplyLevel));

	RegField("CThostFtdcSyncStatusField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcSyncStatusField.TradingDay));
	RegField("CThostFtdcSyncStatusField","数据同步状态","TThostFtdcDataSyncStatusType", "DataSyncStatus", &(m_ThostFtdcSyncStatusField.DataSyncStatus));

	RegField("CThostFtdcQryLinkManField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryLinkManField.BrokerID));
	RegField("CThostFtdcQryLinkManField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryLinkManField.InvestorID));

	RegField("CThostFtdcLinkManField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcLinkManField.BrokerID));
	RegField("CThostFtdcLinkManField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcLinkManField.InvestorID));
	RegField("CThostFtdcLinkManField","联系人类型","TThostFtdcPersonTypeType", "PersonType", &(m_ThostFtdcLinkManField.PersonType));
	RegField("CThostFtdcLinkManField","证件类型","TThostFtdcIdCardTypeType", "IdentifiedCardType", &(m_ThostFtdcLinkManField.IdentifiedCardType));
	RegField("CThostFtdcLinkManField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcLinkManField.IdentifiedCardNo));
	RegField("CThostFtdcLinkManField","名称","TThostFtdcPartyNameType", "PersonName", &(m_ThostFtdcLinkManField.PersonName));
	RegField("CThostFtdcLinkManField","联系电话","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcLinkManField.Telephone));
	RegField("CThostFtdcLinkManField","通讯地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcLinkManField.Address));
	RegField("CThostFtdcLinkManField","邮政编码","TThostFtdcZipCodeType", "ZipCode", &(m_ThostFtdcLinkManField.ZipCode));
	RegField("CThostFtdcLinkManField","优先级","TThostFtdcPriorityType", "Priority", &(m_ThostFtdcLinkManField.Priority));
	RegField("CThostFtdcLinkManField","开户邮政编码","TThostFtdcUOAZipCodeType", "UOAZipCode", &(m_ThostFtdcLinkManField.UOAZipCode));
	RegField("CThostFtdcLinkManField","全称","TThostFtdcInvestorFullNameType", "PersonFullName", &(m_ThostFtdcLinkManField.PersonFullName));

	RegField("CThostFtdcQryBrokerUserEventField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryBrokerUserEventField.BrokerID));
	RegField("CThostFtdcQryBrokerUserEventField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQryBrokerUserEventField.UserID));
	RegField("CThostFtdcQryBrokerUserEventField","用户事件类型","TThostFtdcUserEventTypeType", "UserEventType", &(m_ThostFtdcQryBrokerUserEventField.UserEventType));

	RegField("CThostFtdcBrokerUserEventField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerUserEventField.BrokerID));
	RegField("CThostFtdcBrokerUserEventField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcBrokerUserEventField.UserID));
	RegField("CThostFtdcBrokerUserEventField","用户事件类型","TThostFtdcUserEventTypeType", "UserEventType", &(m_ThostFtdcBrokerUserEventField.UserEventType));
	RegField("CThostFtdcBrokerUserEventField","用户事件序号","TThostFtdcSequenceNoType", "EventSequenceNo", &(m_ThostFtdcBrokerUserEventField.EventSequenceNo));
	RegField("CThostFtdcBrokerUserEventField","事件发生日期","TThostFtdcDateType", "EventDate", &(m_ThostFtdcBrokerUserEventField.EventDate));
	RegField("CThostFtdcBrokerUserEventField","事件发生时间","TThostFtdcTimeType", "EventTime", &(m_ThostFtdcBrokerUserEventField.EventTime));
	RegField("CThostFtdcBrokerUserEventField","用户事件信息","TThostFtdcUserEventInfoType", "UserEventInfo", &(m_ThostFtdcBrokerUserEventField.UserEventInfo));
	RegField("CThostFtdcBrokerUserEventField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcBrokerUserEventField.InvestorID));
	RegField("CThostFtdcBrokerUserEventField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcBrokerUserEventField.InstrumentID));

	RegField("CThostFtdcQryContractBankField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryContractBankField.BrokerID));
	RegField("CThostFtdcQryContractBankField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcQryContractBankField.BankID));
	RegField("CThostFtdcQryContractBankField","银行分中心代码","TThostFtdcBankBrchIDType", "BankBrchID", &(m_ThostFtdcQryContractBankField.BankBrchID));

	RegField("CThostFtdcContractBankField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcContractBankField.BrokerID));
	RegField("CThostFtdcContractBankField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcContractBankField.BankID));
	RegField("CThostFtdcContractBankField","银行分中心代码","TThostFtdcBankBrchIDType", "BankBrchID", &(m_ThostFtdcContractBankField.BankBrchID));
	RegField("CThostFtdcContractBankField","银行名称","TThostFtdcBankNameType", "BankName", &(m_ThostFtdcContractBankField.BankName));

	RegField("CThostFtdcInvestorPositionCombineDetailField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcInvestorPositionCombineDetailField.TradingDay));
	RegField("CThostFtdcInvestorPositionCombineDetailField","开仓日期","TThostFtdcDateType", "OpenDate", &(m_ThostFtdcInvestorPositionCombineDetailField.OpenDate));
	RegField("CThostFtdcInvestorPositionCombineDetailField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcInvestorPositionCombineDetailField.ExchangeID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcInvestorPositionCombineDetailField.SettlementID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorPositionCombineDetailField.BrokerID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInvestorPositionCombineDetailField.InvestorID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","组合编号","TThostFtdcTradeIDType", "ComTradeID", &(m_ThostFtdcInvestorPositionCombineDetailField.ComTradeID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","撮合编号","TThostFtdcTradeIDType", "TradeID", &(m_ThostFtdcInvestorPositionCombineDetailField.TradeID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcInvestorPositionCombineDetailField.InstrumentID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcInvestorPositionCombineDetailField.HedgeFlag));
	RegField("CThostFtdcInvestorPositionCombineDetailField","买卖","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcInvestorPositionCombineDetailField.Direction));
	RegField("CThostFtdcInvestorPositionCombineDetailField","持仓量","TThostFtdcVolumeType", "TotalAmt", &(m_ThostFtdcInvestorPositionCombineDetailField.TotalAmt));
	RegField("CThostFtdcInvestorPositionCombineDetailField","投资者保证金","TThostFtdcMoneyType", "Margin", &(m_ThostFtdcInvestorPositionCombineDetailField.Margin));
	RegField("CThostFtdcInvestorPositionCombineDetailField","交易所保证金","TThostFtdcMoneyType", "ExchMargin", &(m_ThostFtdcInvestorPositionCombineDetailField.ExchMargin));
	RegField("CThostFtdcInvestorPositionCombineDetailField","保证金率","TThostFtdcRatioType", "MarginRateByMoney", &(m_ThostFtdcInvestorPositionCombineDetailField.MarginRateByMoney));
	RegField("CThostFtdcInvestorPositionCombineDetailField","保证金率","TThostFtdcRatioType", "MarginRateByVolume", &(m_ThostFtdcInvestorPositionCombineDetailField.MarginRateByVolume));
	RegField("CThostFtdcInvestorPositionCombineDetailField","单腿编号","TThostFtdcLegIDType", "LegID", &(m_ThostFtdcInvestorPositionCombineDetailField.LegID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","单腿乘数","TThostFtdcLegMultipleType", "LegMultiple", &(m_ThostFtdcInvestorPositionCombineDetailField.LegMultiple));
	RegField("CThostFtdcInvestorPositionCombineDetailField","组合持仓合约编码","TThostFtdcInstrumentIDType", "CombInstrumentID", &(m_ThostFtdcInvestorPositionCombineDetailField.CombInstrumentID));
	RegField("CThostFtdcInvestorPositionCombineDetailField","成交组号","TThostFtdcTradeGroupIDType", "TradeGroupID", &(m_ThostFtdcInvestorPositionCombineDetailField.TradeGroupID));

	RegField("CThostFtdcParkedOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcParkedOrderField.BrokerID));
	RegField("CThostFtdcParkedOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcParkedOrderField.InvestorID));
	RegField("CThostFtdcParkedOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcParkedOrderField.InstrumentID));
	RegField("CThostFtdcParkedOrderField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcParkedOrderField.OrderRef));
	RegField("CThostFtdcParkedOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcParkedOrderField.UserID));
	RegField("CThostFtdcParkedOrderField","报单价格条件","TThostFtdcOrderPriceTypeType", "OrderPriceType", &(m_ThostFtdcParkedOrderField.OrderPriceType));
	RegField("CThostFtdcParkedOrderField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcParkedOrderField.Direction));
	RegField("CThostFtdcParkedOrderField","组合开平标志","TThostFtdcCombOffsetFlagType", "CombOffsetFlag", &(m_ThostFtdcParkedOrderField.CombOffsetFlag));
	RegField("CThostFtdcParkedOrderField","组合投机套保标志","TThostFtdcCombHedgeFlagType", "CombHedgeFlag", &(m_ThostFtdcParkedOrderField.CombHedgeFlag));
	RegField("CThostFtdcParkedOrderField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcParkedOrderField.LimitPrice));
	RegField("CThostFtdcParkedOrderField","数量","TThostFtdcVolumeType", "VolumeTotalOriginal", &(m_ThostFtdcParkedOrderField.VolumeTotalOriginal));
	RegField("CThostFtdcParkedOrderField","有效期类型","TThostFtdcTimeConditionType", "TimeCondition", &(m_ThostFtdcParkedOrderField.TimeCondition));
	RegField("CThostFtdcParkedOrderField","GTD日期","TThostFtdcDateType", "GTDDate", &(m_ThostFtdcParkedOrderField.GTDDate));
	RegField("CThostFtdcParkedOrderField","成交量类型","TThostFtdcVolumeConditionType", "VolumeCondition", &(m_ThostFtdcParkedOrderField.VolumeCondition));
	RegField("CThostFtdcParkedOrderField","最小成交量","TThostFtdcVolumeType", "MinVolume", &(m_ThostFtdcParkedOrderField.MinVolume));
	RegField("CThostFtdcParkedOrderField","触发条件","TThostFtdcContingentConditionType", "ContingentCondition", &(m_ThostFtdcParkedOrderField.ContingentCondition));
	RegField("CThostFtdcParkedOrderField","止损价","TThostFtdcPriceType", "StopPrice", &(m_ThostFtdcParkedOrderField.StopPrice));
	RegField("CThostFtdcParkedOrderField","强平原因","TThostFtdcForceCloseReasonType", "ForceCloseReason", &(m_ThostFtdcParkedOrderField.ForceCloseReason));
	RegField("CThostFtdcParkedOrderField","自动挂起标志","TThostFtdcBoolType", "IsAutoSuspend", &(m_ThostFtdcParkedOrderField.IsAutoSuspend));
	RegField("CThostFtdcParkedOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcParkedOrderField.BusinessUnit));
	RegField("CThostFtdcParkedOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcParkedOrderField.RequestID));
	RegField("CThostFtdcParkedOrderField","用户强评标志","TThostFtdcBoolType", "UserForceClose", &(m_ThostFtdcParkedOrderField.UserForceClose));
	RegField("CThostFtdcParkedOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcParkedOrderField.ExchangeID));
	RegField("CThostFtdcParkedOrderField","预埋报单编号","TThostFtdcParkedOrderIDType", "ParkedOrderID", &(m_ThostFtdcParkedOrderField.ParkedOrderID));
	RegField("CThostFtdcParkedOrderField","用户类型","TThostFtdcUserTypeType", "UserType", &(m_ThostFtdcParkedOrderField.UserType));
	RegField("CThostFtdcParkedOrderField","预埋单状态","TThostFtdcParkedOrderStatusType", "Status", &(m_ThostFtdcParkedOrderField.Status));
	RegField("CThostFtdcParkedOrderField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcParkedOrderField.ErrorID));
	RegField("CThostFtdcParkedOrderField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcParkedOrderField.ErrorMsg));
	RegField("CThostFtdcParkedOrderField","互换单标志","TThostFtdcBoolType", "IsSwapOrder", &(m_ThostFtdcParkedOrderField.IsSwapOrder));

	RegField("CThostFtdcParkedOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcParkedOrderActionField.BrokerID));
	RegField("CThostFtdcParkedOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcParkedOrderActionField.InvestorID));
	RegField("CThostFtdcParkedOrderActionField","报单操作引用","TThostFtdcOrderActionRefType", "OrderActionRef", &(m_ThostFtdcParkedOrderActionField.OrderActionRef));
	RegField("CThostFtdcParkedOrderActionField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcParkedOrderActionField.OrderRef));
	RegField("CThostFtdcParkedOrderActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcParkedOrderActionField.RequestID));
	RegField("CThostFtdcParkedOrderActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcParkedOrderActionField.FrontID));
	RegField("CThostFtdcParkedOrderActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcParkedOrderActionField.SessionID));
	RegField("CThostFtdcParkedOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcParkedOrderActionField.ExchangeID));
	RegField("CThostFtdcParkedOrderActionField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcParkedOrderActionField.OrderSysID));
	RegField("CThostFtdcParkedOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcParkedOrderActionField.ActionFlag));
	RegField("CThostFtdcParkedOrderActionField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcParkedOrderActionField.LimitPrice));
	RegField("CThostFtdcParkedOrderActionField","数量变化","TThostFtdcVolumeType", "VolumeChange", &(m_ThostFtdcParkedOrderActionField.VolumeChange));
	RegField("CThostFtdcParkedOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcParkedOrderActionField.UserID));
	RegField("CThostFtdcParkedOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcParkedOrderActionField.InstrumentID));
	RegField("CThostFtdcParkedOrderActionField","预埋撤单单编号","TThostFtdcParkedOrderActionIDType", "ParkedOrderActionID", &(m_ThostFtdcParkedOrderActionField.ParkedOrderActionID));
	RegField("CThostFtdcParkedOrderActionField","用户类型","TThostFtdcUserTypeType", "UserType", &(m_ThostFtdcParkedOrderActionField.UserType));
	RegField("CThostFtdcParkedOrderActionField","预埋撤单状态","TThostFtdcParkedOrderStatusType", "Status", &(m_ThostFtdcParkedOrderActionField.Status));
	RegField("CThostFtdcParkedOrderActionField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcParkedOrderActionField.ErrorID));
	RegField("CThostFtdcParkedOrderActionField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcParkedOrderActionField.ErrorMsg));

	RegField("CThostFtdcQryParkedOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryParkedOrderField.BrokerID));
	RegField("CThostFtdcQryParkedOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryParkedOrderField.InvestorID));
	RegField("CThostFtdcQryParkedOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryParkedOrderField.InstrumentID));
	RegField("CThostFtdcQryParkedOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryParkedOrderField.ExchangeID));

	RegField("CThostFtdcQryParkedOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryParkedOrderActionField.BrokerID));
	RegField("CThostFtdcQryParkedOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryParkedOrderActionField.InvestorID));
	RegField("CThostFtdcQryParkedOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryParkedOrderActionField.InstrumentID));
	RegField("CThostFtdcQryParkedOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryParkedOrderActionField.ExchangeID));

	RegField("CThostFtdcRemoveParkedOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRemoveParkedOrderField.BrokerID));
	RegField("CThostFtdcRemoveParkedOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcRemoveParkedOrderField.InvestorID));
	RegField("CThostFtdcRemoveParkedOrderField","预埋报单编号","TThostFtdcParkedOrderIDType", "ParkedOrderID", &(m_ThostFtdcRemoveParkedOrderField.ParkedOrderID));

	RegField("CThostFtdcRemoveParkedOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRemoveParkedOrderActionField.BrokerID));
	RegField("CThostFtdcRemoveParkedOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcRemoveParkedOrderActionField.InvestorID));
	RegField("CThostFtdcRemoveParkedOrderActionField","预埋撤单编号","TThostFtdcParkedOrderActionIDType", "ParkedOrderActionID", &(m_ThostFtdcRemoveParkedOrderActionField.ParkedOrderActionID));

	RegField("CThostFtdcInvestorWithdrawAlgorithmField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorWithdrawAlgorithmField.BrokerID));
	RegField("CThostFtdcInvestorWithdrawAlgorithmField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcInvestorWithdrawAlgorithmField.InvestorRange));
	RegField("CThostFtdcInvestorWithdrawAlgorithmField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInvestorWithdrawAlgorithmField.InvestorID));
	RegField("CThostFtdcInvestorWithdrawAlgorithmField","可提资金比例","TThostFtdcRatioType", "UsingRatio", &(m_ThostFtdcInvestorWithdrawAlgorithmField.UsingRatio));
	RegField("CThostFtdcInvestorWithdrawAlgorithmField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcInvestorWithdrawAlgorithmField.CurrencyID));
	RegField("CThostFtdcInvestorWithdrawAlgorithmField","货币质押比率","TThostFtdcRatioType", "FundMortgageRatio", &(m_ThostFtdcInvestorWithdrawAlgorithmField.FundMortgageRatio));

	RegField("CThostFtdcQryInvestorPositionCombineDetailField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInvestorPositionCombineDetailField.BrokerID));
	RegField("CThostFtdcQryInvestorPositionCombineDetailField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInvestorPositionCombineDetailField.InvestorID));
	RegField("CThostFtdcQryInvestorPositionCombineDetailField","组合持仓合约编码","TThostFtdcInstrumentIDType", "CombInstrumentID", &(m_ThostFtdcQryInvestorPositionCombineDetailField.CombInstrumentID));

	RegField("CThostFtdcMarketDataAveragePriceField","当日均价","TThostFtdcPriceType", "AveragePrice", &(m_ThostFtdcMarketDataAveragePriceField.AveragePrice));

	RegField("CThostFtdcVerifyInvestorPasswordField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcVerifyInvestorPasswordField.BrokerID));
	RegField("CThostFtdcVerifyInvestorPasswordField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcVerifyInvestorPasswordField.InvestorID));
	RegField("CThostFtdcVerifyInvestorPasswordField","密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcVerifyInvestorPasswordField.Password));

	RegField("CThostFtdcUserIPField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcUserIPField.BrokerID));
	RegField("CThostFtdcUserIPField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcUserIPField.UserID));
	RegField("CThostFtdcUserIPField","IP地址","TThostFtdcIPAddressType", "IPAddress", &(m_ThostFtdcUserIPField.IPAddress));
	RegField("CThostFtdcUserIPField","IP地址掩码","TThostFtdcIPAddressType", "IPMask", &(m_ThostFtdcUserIPField.IPMask));
	RegField("CThostFtdcUserIPField","Mac地址","TThostFtdcMacAddressType", "MacAddress", &(m_ThostFtdcUserIPField.MacAddress));

	RegField("CThostFtdcTradingNoticeInfoField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingNoticeInfoField.BrokerID));
	RegField("CThostFtdcTradingNoticeInfoField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcTradingNoticeInfoField.InvestorID));
	RegField("CThostFtdcTradingNoticeInfoField","发送时间","TThostFtdcTimeType", "SendTime", &(m_ThostFtdcTradingNoticeInfoField.SendTime));
	RegField("CThostFtdcTradingNoticeInfoField","消息正文","TThostFtdcContentType", "FieldContent", &(m_ThostFtdcTradingNoticeInfoField.FieldContent));
	RegField("CThostFtdcTradingNoticeInfoField","序列系列号","TThostFtdcSequenceSeriesType", "SequenceSeries", &(m_ThostFtdcTradingNoticeInfoField.SequenceSeries));
	RegField("CThostFtdcTradingNoticeInfoField","序列号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcTradingNoticeInfoField.SequenceNo));

	RegField("CThostFtdcTradingNoticeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingNoticeField.BrokerID));
	RegField("CThostFtdcTradingNoticeField","投资者范围","TThostFtdcInvestorRangeType", "InvestorRange", &(m_ThostFtdcTradingNoticeField.InvestorRange));
	RegField("CThostFtdcTradingNoticeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcTradingNoticeField.InvestorID));
	RegField("CThostFtdcTradingNoticeField","序列系列号","TThostFtdcSequenceSeriesType", "SequenceSeries", &(m_ThostFtdcTradingNoticeField.SequenceSeries));
	RegField("CThostFtdcTradingNoticeField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcTradingNoticeField.UserID));
	RegField("CThostFtdcTradingNoticeField","发送时间","TThostFtdcTimeType", "SendTime", &(m_ThostFtdcTradingNoticeField.SendTime));
	RegField("CThostFtdcTradingNoticeField","序列号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcTradingNoticeField.SequenceNo));
	RegField("CThostFtdcTradingNoticeField","消息正文","TThostFtdcContentType", "FieldContent", &(m_ThostFtdcTradingNoticeField.FieldContent));

	RegField("CThostFtdcQryTradingNoticeField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryTradingNoticeField.BrokerID));
	RegField("CThostFtdcQryTradingNoticeField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryTradingNoticeField.InvestorID));

	RegField("CThostFtdcQryErrOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryErrOrderField.BrokerID));
	RegField("CThostFtdcQryErrOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryErrOrderField.InvestorID));

	RegField("CThostFtdcErrOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcErrOrderField.BrokerID));
	RegField("CThostFtdcErrOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcErrOrderField.InvestorID));
	RegField("CThostFtdcErrOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcErrOrderField.InstrumentID));
	RegField("CThostFtdcErrOrderField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcErrOrderField.OrderRef));
	RegField("CThostFtdcErrOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcErrOrderField.UserID));
	RegField("CThostFtdcErrOrderField","报单价格条件","TThostFtdcOrderPriceTypeType", "OrderPriceType", &(m_ThostFtdcErrOrderField.OrderPriceType));
	RegField("CThostFtdcErrOrderField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcErrOrderField.Direction));
	RegField("CThostFtdcErrOrderField","组合开平标志","TThostFtdcCombOffsetFlagType", "CombOffsetFlag", &(m_ThostFtdcErrOrderField.CombOffsetFlag));
	RegField("CThostFtdcErrOrderField","组合投机套保标志","TThostFtdcCombHedgeFlagType", "CombHedgeFlag", &(m_ThostFtdcErrOrderField.CombHedgeFlag));
	RegField("CThostFtdcErrOrderField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcErrOrderField.LimitPrice));
	RegField("CThostFtdcErrOrderField","数量","TThostFtdcVolumeType", "VolumeTotalOriginal", &(m_ThostFtdcErrOrderField.VolumeTotalOriginal));
	RegField("CThostFtdcErrOrderField","有效期类型","TThostFtdcTimeConditionType", "TimeCondition", &(m_ThostFtdcErrOrderField.TimeCondition));
	RegField("CThostFtdcErrOrderField","GTD日期","TThostFtdcDateType", "GTDDate", &(m_ThostFtdcErrOrderField.GTDDate));
	RegField("CThostFtdcErrOrderField","成交量类型","TThostFtdcVolumeConditionType", "VolumeCondition", &(m_ThostFtdcErrOrderField.VolumeCondition));
	RegField("CThostFtdcErrOrderField","最小成交量","TThostFtdcVolumeType", "MinVolume", &(m_ThostFtdcErrOrderField.MinVolume));
	RegField("CThostFtdcErrOrderField","触发条件","TThostFtdcContingentConditionType", "ContingentCondition", &(m_ThostFtdcErrOrderField.ContingentCondition));
	RegField("CThostFtdcErrOrderField","止损价","TThostFtdcPriceType", "StopPrice", &(m_ThostFtdcErrOrderField.StopPrice));
	RegField("CThostFtdcErrOrderField","强平原因","TThostFtdcForceCloseReasonType", "ForceCloseReason", &(m_ThostFtdcErrOrderField.ForceCloseReason));
	RegField("CThostFtdcErrOrderField","自动挂起标志","TThostFtdcBoolType", "IsAutoSuspend", &(m_ThostFtdcErrOrderField.IsAutoSuspend));
	RegField("CThostFtdcErrOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcErrOrderField.BusinessUnit));
	RegField("CThostFtdcErrOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcErrOrderField.RequestID));
	RegField("CThostFtdcErrOrderField","用户强评标志","TThostFtdcBoolType", "UserForceClose", &(m_ThostFtdcErrOrderField.UserForceClose));
	RegField("CThostFtdcErrOrderField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcErrOrderField.ErrorID));
	RegField("CThostFtdcErrOrderField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcErrOrderField.ErrorMsg));
	RegField("CThostFtdcErrOrderField","互换单标志","TThostFtdcBoolType", "IsSwapOrder", &(m_ThostFtdcErrOrderField.IsSwapOrder));

	RegField("CThostFtdcErrorConditionalOrderField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcErrorConditionalOrderField.BrokerID));
	RegField("CThostFtdcErrorConditionalOrderField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcErrorConditionalOrderField.InvestorID));
	RegField("CThostFtdcErrorConditionalOrderField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcErrorConditionalOrderField.InstrumentID));
	RegField("CThostFtdcErrorConditionalOrderField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcErrorConditionalOrderField.OrderRef));
	RegField("CThostFtdcErrorConditionalOrderField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcErrorConditionalOrderField.UserID));
	RegField("CThostFtdcErrorConditionalOrderField","报单价格条件","TThostFtdcOrderPriceTypeType", "OrderPriceType", &(m_ThostFtdcErrorConditionalOrderField.OrderPriceType));
	RegField("CThostFtdcErrorConditionalOrderField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcErrorConditionalOrderField.Direction));
	RegField("CThostFtdcErrorConditionalOrderField","组合开平标志","TThostFtdcCombOffsetFlagType", "CombOffsetFlag", &(m_ThostFtdcErrorConditionalOrderField.CombOffsetFlag));
	RegField("CThostFtdcErrorConditionalOrderField","组合投机套保标志","TThostFtdcCombHedgeFlagType", "CombHedgeFlag", &(m_ThostFtdcErrorConditionalOrderField.CombHedgeFlag));
	RegField("CThostFtdcErrorConditionalOrderField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcErrorConditionalOrderField.LimitPrice));
	RegField("CThostFtdcErrorConditionalOrderField","数量","TThostFtdcVolumeType", "VolumeTotalOriginal", &(m_ThostFtdcErrorConditionalOrderField.VolumeTotalOriginal));
	RegField("CThostFtdcErrorConditionalOrderField","有效期类型","TThostFtdcTimeConditionType", "TimeCondition", &(m_ThostFtdcErrorConditionalOrderField.TimeCondition));
	RegField("CThostFtdcErrorConditionalOrderField","GTD日期","TThostFtdcDateType", "GTDDate", &(m_ThostFtdcErrorConditionalOrderField.GTDDate));
	RegField("CThostFtdcErrorConditionalOrderField","成交量类型","TThostFtdcVolumeConditionType", "VolumeCondition", &(m_ThostFtdcErrorConditionalOrderField.VolumeCondition));
	RegField("CThostFtdcErrorConditionalOrderField","最小成交量","TThostFtdcVolumeType", "MinVolume", &(m_ThostFtdcErrorConditionalOrderField.MinVolume));
	RegField("CThostFtdcErrorConditionalOrderField","触发条件","TThostFtdcContingentConditionType", "ContingentCondition", &(m_ThostFtdcErrorConditionalOrderField.ContingentCondition));
	RegField("CThostFtdcErrorConditionalOrderField","止损价","TThostFtdcPriceType", "StopPrice", &(m_ThostFtdcErrorConditionalOrderField.StopPrice));
	RegField("CThostFtdcErrorConditionalOrderField","强平原因","TThostFtdcForceCloseReasonType", "ForceCloseReason", &(m_ThostFtdcErrorConditionalOrderField.ForceCloseReason));
	RegField("CThostFtdcErrorConditionalOrderField","自动挂起标志","TThostFtdcBoolType", "IsAutoSuspend", &(m_ThostFtdcErrorConditionalOrderField.IsAutoSuspend));
	RegField("CThostFtdcErrorConditionalOrderField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcErrorConditionalOrderField.BusinessUnit));
	RegField("CThostFtdcErrorConditionalOrderField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcErrorConditionalOrderField.RequestID));
	RegField("CThostFtdcErrorConditionalOrderField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcErrorConditionalOrderField.OrderLocalID));
	RegField("CThostFtdcErrorConditionalOrderField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcErrorConditionalOrderField.ExchangeID));
	RegField("CThostFtdcErrorConditionalOrderField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcErrorConditionalOrderField.ParticipantID));
	RegField("CThostFtdcErrorConditionalOrderField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcErrorConditionalOrderField.ClientID));
	RegField("CThostFtdcErrorConditionalOrderField","合约在交易所的代码","TThostFtdcExchangeInstIDType", "ExchangeInstID", &(m_ThostFtdcErrorConditionalOrderField.ExchangeInstID));
	RegField("CThostFtdcErrorConditionalOrderField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcErrorConditionalOrderField.TraderID));
	RegField("CThostFtdcErrorConditionalOrderField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcErrorConditionalOrderField.InstallID));
	RegField("CThostFtdcErrorConditionalOrderField","报单提交状态","TThostFtdcOrderSubmitStatusType", "OrderSubmitStatus", &(m_ThostFtdcErrorConditionalOrderField.OrderSubmitStatus));
	RegField("CThostFtdcErrorConditionalOrderField","报单提示序号","TThostFtdcSequenceNoType", "NotifySequence", &(m_ThostFtdcErrorConditionalOrderField.NotifySequence));
	RegField("CThostFtdcErrorConditionalOrderField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcErrorConditionalOrderField.TradingDay));
	RegField("CThostFtdcErrorConditionalOrderField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcErrorConditionalOrderField.SettlementID));
	RegField("CThostFtdcErrorConditionalOrderField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcErrorConditionalOrderField.OrderSysID));
	RegField("CThostFtdcErrorConditionalOrderField","报单来源","TThostFtdcOrderSourceType", "OrderSource", &(m_ThostFtdcErrorConditionalOrderField.OrderSource));
	RegField("CThostFtdcErrorConditionalOrderField","报单状态","TThostFtdcOrderStatusType", "OrderStatus", &(m_ThostFtdcErrorConditionalOrderField.OrderStatus));
	RegField("CThostFtdcErrorConditionalOrderField","报单类型","TThostFtdcOrderTypeType", "OrderType", &(m_ThostFtdcErrorConditionalOrderField.OrderType));
	RegField("CThostFtdcErrorConditionalOrderField","今成交数量","TThostFtdcVolumeType", "VolumeTraded", &(m_ThostFtdcErrorConditionalOrderField.VolumeTraded));
	RegField("CThostFtdcErrorConditionalOrderField","剩余数量","TThostFtdcVolumeType", "VolumeTotal", &(m_ThostFtdcErrorConditionalOrderField.VolumeTotal));
	RegField("CThostFtdcErrorConditionalOrderField","报单日期","TThostFtdcDateType", "InsertDate", &(m_ThostFtdcErrorConditionalOrderField.InsertDate));
	RegField("CThostFtdcErrorConditionalOrderField","委托时间","TThostFtdcTimeType", "InsertTime", &(m_ThostFtdcErrorConditionalOrderField.InsertTime));
	RegField("CThostFtdcErrorConditionalOrderField","激活时间","TThostFtdcTimeType", "ActiveTime", &(m_ThostFtdcErrorConditionalOrderField.ActiveTime));
	RegField("CThostFtdcErrorConditionalOrderField","挂起时间","TThostFtdcTimeType", "SuspendTime", &(m_ThostFtdcErrorConditionalOrderField.SuspendTime));
	RegField("CThostFtdcErrorConditionalOrderField","最后修改时间","TThostFtdcTimeType", "UpdateTime", &(m_ThostFtdcErrorConditionalOrderField.UpdateTime));
	RegField("CThostFtdcErrorConditionalOrderField","撤销时间","TThostFtdcTimeType", "CancelTime", &(m_ThostFtdcErrorConditionalOrderField.CancelTime));
	RegField("CThostFtdcErrorConditionalOrderField","最后修改交易所交易员代码","TThostFtdcTraderIDType", "ActiveTraderID", &(m_ThostFtdcErrorConditionalOrderField.ActiveTraderID));
	RegField("CThostFtdcErrorConditionalOrderField","结算会员编号","TThostFtdcParticipantIDType", "ClearingPartID", &(m_ThostFtdcErrorConditionalOrderField.ClearingPartID));
	RegField("CThostFtdcErrorConditionalOrderField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcErrorConditionalOrderField.SequenceNo));
	RegField("CThostFtdcErrorConditionalOrderField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcErrorConditionalOrderField.FrontID));
	RegField("CThostFtdcErrorConditionalOrderField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcErrorConditionalOrderField.SessionID));
	RegField("CThostFtdcErrorConditionalOrderField","用户端产品信息","TThostFtdcProductInfoType", "UserProductInfo", &(m_ThostFtdcErrorConditionalOrderField.UserProductInfo));
	RegField("CThostFtdcErrorConditionalOrderField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcErrorConditionalOrderField.StatusMsg));
	RegField("CThostFtdcErrorConditionalOrderField","用户强评标志","TThostFtdcBoolType", "UserForceClose", &(m_ThostFtdcErrorConditionalOrderField.UserForceClose));
	RegField("CThostFtdcErrorConditionalOrderField","操作用户代码","TThostFtdcUserIDType", "ActiveUserID", &(m_ThostFtdcErrorConditionalOrderField.ActiveUserID));
	RegField("CThostFtdcErrorConditionalOrderField","经纪公司报单编号","TThostFtdcSequenceNoType", "BrokerOrderSeq", &(m_ThostFtdcErrorConditionalOrderField.BrokerOrderSeq));
	RegField("CThostFtdcErrorConditionalOrderField","相关报单","TThostFtdcOrderSysIDType", "RelativeOrderSysID", &(m_ThostFtdcErrorConditionalOrderField.RelativeOrderSysID));
	RegField("CThostFtdcErrorConditionalOrderField","郑商所成交数量","TThostFtdcVolumeType", "ZCETotalTradedVolume", &(m_ThostFtdcErrorConditionalOrderField.ZCETotalTradedVolume));
	RegField("CThostFtdcErrorConditionalOrderField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcErrorConditionalOrderField.ErrorID));
	RegField("CThostFtdcErrorConditionalOrderField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcErrorConditionalOrderField.ErrorMsg));
	RegField("CThostFtdcErrorConditionalOrderField","互换单标志","TThostFtdcBoolType", "IsSwapOrder", &(m_ThostFtdcErrorConditionalOrderField.IsSwapOrder));

	RegField("CThostFtdcQryErrOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryErrOrderActionField.BrokerID));
	RegField("CThostFtdcQryErrOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryErrOrderActionField.InvestorID));

	RegField("CThostFtdcErrOrderActionField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcErrOrderActionField.BrokerID));
	RegField("CThostFtdcErrOrderActionField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcErrOrderActionField.InvestorID));
	RegField("CThostFtdcErrOrderActionField","报单操作引用","TThostFtdcOrderActionRefType", "OrderActionRef", &(m_ThostFtdcErrOrderActionField.OrderActionRef));
	RegField("CThostFtdcErrOrderActionField","报单引用","TThostFtdcOrderRefType", "OrderRef", &(m_ThostFtdcErrOrderActionField.OrderRef));
	RegField("CThostFtdcErrOrderActionField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcErrOrderActionField.RequestID));
	RegField("CThostFtdcErrOrderActionField","前置编号","TThostFtdcFrontIDType", "FrontID", &(m_ThostFtdcErrOrderActionField.FrontID));
	RegField("CThostFtdcErrOrderActionField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcErrOrderActionField.SessionID));
	RegField("CThostFtdcErrOrderActionField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcErrOrderActionField.ExchangeID));
	RegField("CThostFtdcErrOrderActionField","报单编号","TThostFtdcOrderSysIDType", "OrderSysID", &(m_ThostFtdcErrOrderActionField.OrderSysID));
	RegField("CThostFtdcErrOrderActionField","操作标志","TThostFtdcActionFlagType", "ActionFlag", &(m_ThostFtdcErrOrderActionField.ActionFlag));
	RegField("CThostFtdcErrOrderActionField","价格","TThostFtdcPriceType", "LimitPrice", &(m_ThostFtdcErrOrderActionField.LimitPrice));
	RegField("CThostFtdcErrOrderActionField","数量变化","TThostFtdcVolumeType", "VolumeChange", &(m_ThostFtdcErrOrderActionField.VolumeChange));
	RegField("CThostFtdcErrOrderActionField","操作日期","TThostFtdcDateType", "ActionDate", &(m_ThostFtdcErrOrderActionField.ActionDate));
	RegField("CThostFtdcErrOrderActionField","操作时间","TThostFtdcTimeType", "ActionTime", &(m_ThostFtdcErrOrderActionField.ActionTime));
	RegField("CThostFtdcErrOrderActionField","交易所交易员代码","TThostFtdcTraderIDType", "TraderID", &(m_ThostFtdcErrOrderActionField.TraderID));
	RegField("CThostFtdcErrOrderActionField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcErrOrderActionField.InstallID));
	RegField("CThostFtdcErrOrderActionField","本地报单编号","TThostFtdcOrderLocalIDType", "OrderLocalID", &(m_ThostFtdcErrOrderActionField.OrderLocalID));
	RegField("CThostFtdcErrOrderActionField","操作本地编号","TThostFtdcOrderLocalIDType", "ActionLocalID", &(m_ThostFtdcErrOrderActionField.ActionLocalID));
	RegField("CThostFtdcErrOrderActionField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcErrOrderActionField.ParticipantID));
	RegField("CThostFtdcErrOrderActionField","客户代码","TThostFtdcClientIDType", "ClientID", &(m_ThostFtdcErrOrderActionField.ClientID));
	RegField("CThostFtdcErrOrderActionField","业务单元","TThostFtdcBusinessUnitType", "BusinessUnit", &(m_ThostFtdcErrOrderActionField.BusinessUnit));
	RegField("CThostFtdcErrOrderActionField","报单操作状态","TThostFtdcOrderActionStatusType", "OrderActionStatus", &(m_ThostFtdcErrOrderActionField.OrderActionStatus));
	RegField("CThostFtdcErrOrderActionField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcErrOrderActionField.UserID));
	RegField("CThostFtdcErrOrderActionField","状态信息","TThostFtdcErrorMsgType", "StatusMsg", &(m_ThostFtdcErrOrderActionField.StatusMsg));
	RegField("CThostFtdcErrOrderActionField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcErrOrderActionField.InstrumentID));
	RegField("CThostFtdcErrOrderActionField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcErrOrderActionField.ErrorID));
	RegField("CThostFtdcErrOrderActionField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcErrOrderActionField.ErrorMsg));

	RegField("CThostFtdcQryExchangeSequenceField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryExchangeSequenceField.ExchangeID));

	RegField("CThostFtdcExchangeSequenceField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcExchangeSequenceField.ExchangeID));
	RegField("CThostFtdcExchangeSequenceField","序号","TThostFtdcSequenceNoType", "SequenceNo", &(m_ThostFtdcExchangeSequenceField.SequenceNo));
	RegField("CThostFtdcExchangeSequenceField","合约交易状态","TThostFtdcInstrumentStatusType", "MarketStatus", &(m_ThostFtdcExchangeSequenceField.MarketStatus));

	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.BrokerID));
	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.InvestorID));
	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.InstrumentID));
	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.Direction));
	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","开平标志","TThostFtdcOffsetFlagType", "OffsetFlag", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.OffsetFlag));
	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.HedgeFlag));
	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","最大允许报单数量","TThostFtdcVolumeType", "MaxVolume", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.MaxVolume));
	RegField("CThostFtdcQueryMaxOrderVolumeWithPriceField","报单价格","TThostFtdcPriceType", "Price", &(m_ThostFtdcQueryMaxOrderVolumeWithPriceField.Price));

	RegField("CThostFtdcQryBrokerTradingParamsField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryBrokerTradingParamsField.BrokerID));
	RegField("CThostFtdcQryBrokerTradingParamsField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryBrokerTradingParamsField.InvestorID));
	RegField("CThostFtdcQryBrokerTradingParamsField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcQryBrokerTradingParamsField.CurrencyID));

	RegField("CThostFtdcBrokerTradingParamsField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerTradingParamsField.BrokerID));
	RegField("CThostFtdcBrokerTradingParamsField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcBrokerTradingParamsField.InvestorID));
	RegField("CThostFtdcBrokerTradingParamsField","保证金价格类型","TThostFtdcMarginPriceTypeType", "MarginPriceType", &(m_ThostFtdcBrokerTradingParamsField.MarginPriceType));
	RegField("CThostFtdcBrokerTradingParamsField","盈亏算法","TThostFtdcAlgorithmType", "Algorithm", &(m_ThostFtdcBrokerTradingParamsField.Algorithm));
	RegField("CThostFtdcBrokerTradingParamsField","可用是否包含平仓盈利","TThostFtdcIncludeCloseProfitType", "AvailIncludeCloseProfit", &(m_ThostFtdcBrokerTradingParamsField.AvailIncludeCloseProfit));
	RegField("CThostFtdcBrokerTradingParamsField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcBrokerTradingParamsField.CurrencyID));
	RegField("CThostFtdcBrokerTradingParamsField","期权权利金价格类型","TThostFtdcOptionRoyaltyPriceTypeType", "OptionRoyaltyPriceType", &(m_ThostFtdcBrokerTradingParamsField.OptionRoyaltyPriceType));

	RegField("CThostFtdcQryBrokerTradingAlgosField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryBrokerTradingAlgosField.BrokerID));
	RegField("CThostFtdcQryBrokerTradingAlgosField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryBrokerTradingAlgosField.ExchangeID));
	RegField("CThostFtdcQryBrokerTradingAlgosField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryBrokerTradingAlgosField.InstrumentID));

	RegField("CThostFtdcBrokerTradingAlgosField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerTradingAlgosField.BrokerID));
	RegField("CThostFtdcBrokerTradingAlgosField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcBrokerTradingAlgosField.ExchangeID));
	RegField("CThostFtdcBrokerTradingAlgosField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcBrokerTradingAlgosField.InstrumentID));
	RegField("CThostFtdcBrokerTradingAlgosField","持仓处理算法编号","TThostFtdcHandlePositionAlgoIDType", "HandlePositionAlgoID", &(m_ThostFtdcBrokerTradingAlgosField.HandlePositionAlgoID));
	RegField("CThostFtdcBrokerTradingAlgosField","寻找保证金率算法编号","TThostFtdcFindMarginRateAlgoIDType", "FindMarginRateAlgoID", &(m_ThostFtdcBrokerTradingAlgosField.FindMarginRateAlgoID));
	RegField("CThostFtdcBrokerTradingAlgosField","资金处理算法编号","TThostFtdcHandleTradingAccountAlgoIDType", "HandleTradingAccountAlgoID", &(m_ThostFtdcBrokerTradingAlgosField.HandleTradingAccountAlgoID));

	RegField("CThostFtdcQueryBrokerDepositField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQueryBrokerDepositField.BrokerID));
	RegField("CThostFtdcQueryBrokerDepositField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQueryBrokerDepositField.ExchangeID));

	RegField("CThostFtdcBrokerDepositField","交易日期","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcBrokerDepositField.TradingDay));
	RegField("CThostFtdcBrokerDepositField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerDepositField.BrokerID));
	RegField("CThostFtdcBrokerDepositField","会员代码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcBrokerDepositField.ParticipantID));
	RegField("CThostFtdcBrokerDepositField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcBrokerDepositField.ExchangeID));
	RegField("CThostFtdcBrokerDepositField","上次结算准备金","TThostFtdcMoneyType", "PreBalance", &(m_ThostFtdcBrokerDepositField.PreBalance));
	RegField("CThostFtdcBrokerDepositField","当前保证金总额","TThostFtdcMoneyType", "CurrMargin", &(m_ThostFtdcBrokerDepositField.CurrMargin));
	RegField("CThostFtdcBrokerDepositField","平仓盈亏","TThostFtdcMoneyType", "CloseProfit", &(m_ThostFtdcBrokerDepositField.CloseProfit));
	RegField("CThostFtdcBrokerDepositField","期货结算准备金","TThostFtdcMoneyType", "Balance", &(m_ThostFtdcBrokerDepositField.Balance));
	RegField("CThostFtdcBrokerDepositField","入金金额","TThostFtdcMoneyType", "Deposit", &(m_ThostFtdcBrokerDepositField.Deposit));
	RegField("CThostFtdcBrokerDepositField","出金金额","TThostFtdcMoneyType", "Withdraw", &(m_ThostFtdcBrokerDepositField.Withdraw));
	RegField("CThostFtdcBrokerDepositField","可提资金","TThostFtdcMoneyType", "Available", &(m_ThostFtdcBrokerDepositField.Available));
	RegField("CThostFtdcBrokerDepositField","基本准备金","TThostFtdcMoneyType", "Reserve", &(m_ThostFtdcBrokerDepositField.Reserve));
	RegField("CThostFtdcBrokerDepositField","冻结的保证金","TThostFtdcMoneyType", "FrozenMargin", &(m_ThostFtdcBrokerDepositField.FrozenMargin));

	RegField("CThostFtdcQryCFMMCBrokerKeyField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryCFMMCBrokerKeyField.BrokerID));

	RegField("CThostFtdcCFMMCBrokerKeyField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcCFMMCBrokerKeyField.BrokerID));
	RegField("CThostFtdcCFMMCBrokerKeyField","经纪公司统一编码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcCFMMCBrokerKeyField.ParticipantID));
	RegField("CThostFtdcCFMMCBrokerKeyField","密钥生成日期","TThostFtdcDateType", "CreateDate", &(m_ThostFtdcCFMMCBrokerKeyField.CreateDate));
	RegField("CThostFtdcCFMMCBrokerKeyField","密钥生成时间","TThostFtdcTimeType", "CreateTime", &(m_ThostFtdcCFMMCBrokerKeyField.CreateTime));
	RegField("CThostFtdcCFMMCBrokerKeyField","密钥编号","TThostFtdcSequenceNoType", "KeyID", &(m_ThostFtdcCFMMCBrokerKeyField.KeyID));
	RegField("CThostFtdcCFMMCBrokerKeyField","动态密钥","TThostFtdcCFMMCKeyType", "CurrentKey", &(m_ThostFtdcCFMMCBrokerKeyField.CurrentKey));
	RegField("CThostFtdcCFMMCBrokerKeyField","动态密钥类型","TThostFtdcCFMMCKeyKindType", "KeyKind", &(m_ThostFtdcCFMMCBrokerKeyField.KeyKind));

	RegField("CThostFtdcCFMMCTradingAccountKeyField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcCFMMCTradingAccountKeyField.BrokerID));
	RegField("CThostFtdcCFMMCTradingAccountKeyField","经纪公司统一编码","TThostFtdcParticipantIDType", "ParticipantID", &(m_ThostFtdcCFMMCTradingAccountKeyField.ParticipantID));
	RegField("CThostFtdcCFMMCTradingAccountKeyField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcCFMMCTradingAccountKeyField.AccountID));
	RegField("CThostFtdcCFMMCTradingAccountKeyField","密钥编号","TThostFtdcSequenceNoType", "KeyID", &(m_ThostFtdcCFMMCTradingAccountKeyField.KeyID));
	RegField("CThostFtdcCFMMCTradingAccountKeyField","动态密钥","TThostFtdcCFMMCKeyType", "CurrentKey", &(m_ThostFtdcCFMMCTradingAccountKeyField.CurrentKey));

	RegField("CThostFtdcQryCFMMCTradingAccountKeyField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryCFMMCTradingAccountKeyField.BrokerID));
	RegField("CThostFtdcQryCFMMCTradingAccountKeyField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryCFMMCTradingAccountKeyField.InvestorID));

	RegField("CThostFtdcBrokerUserOTPParamField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerUserOTPParamField.BrokerID));
	RegField("CThostFtdcBrokerUserOTPParamField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcBrokerUserOTPParamField.UserID));
	RegField("CThostFtdcBrokerUserOTPParamField","动态令牌提供商","TThostFtdcOTPVendorsIDType", "OTPVendorsID", &(m_ThostFtdcBrokerUserOTPParamField.OTPVendorsID));
	RegField("CThostFtdcBrokerUserOTPParamField","动态令牌序列号","TThostFtdcSerialNumberType", "SerialNumber", &(m_ThostFtdcBrokerUserOTPParamField.SerialNumber));
	RegField("CThostFtdcBrokerUserOTPParamField","令牌密钥","TThostFtdcAuthKeyType", "AuthKey", &(m_ThostFtdcBrokerUserOTPParamField.AuthKey));
	RegField("CThostFtdcBrokerUserOTPParamField","漂移值","TThostFtdcLastDriftType", "LastDrift", &(m_ThostFtdcBrokerUserOTPParamField.LastDrift));
	RegField("CThostFtdcBrokerUserOTPParamField","成功值","TThostFtdcLastSuccessType", "LastSuccess", &(m_ThostFtdcBrokerUserOTPParamField.LastSuccess));
	RegField("CThostFtdcBrokerUserOTPParamField","动态令牌类型","TThostFtdcOTPTypeType", "OTPType", &(m_ThostFtdcBrokerUserOTPParamField.OTPType));

	RegField("CThostFtdcManualSyncBrokerUserOTPField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcManualSyncBrokerUserOTPField.BrokerID));
	RegField("CThostFtdcManualSyncBrokerUserOTPField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcManualSyncBrokerUserOTPField.UserID));
	RegField("CThostFtdcManualSyncBrokerUserOTPField","动态令牌类型","TThostFtdcOTPTypeType", "OTPType", &(m_ThostFtdcManualSyncBrokerUserOTPField.OTPType));
	RegField("CThostFtdcManualSyncBrokerUserOTPField","第一个动态密码","TThostFtdcPasswordType", "FirstOTP", &(m_ThostFtdcManualSyncBrokerUserOTPField.FirstOTP));
	RegField("CThostFtdcManualSyncBrokerUserOTPField","第二个动态密码","TThostFtdcPasswordType", "SecondOTP", &(m_ThostFtdcManualSyncBrokerUserOTPField.SecondOTP));

	RegField("CThostFtdcCommRateModelField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcCommRateModelField.BrokerID));
	RegField("CThostFtdcCommRateModelField","手续费率模板代码","TThostFtdcInvestorIDType", "CommModelID", &(m_ThostFtdcCommRateModelField.CommModelID));
	RegField("CThostFtdcCommRateModelField","模板名称","TThostFtdcCommModelNameType", "CommModelName", &(m_ThostFtdcCommRateModelField.CommModelName));

	RegField("CThostFtdcQryCommRateModelField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryCommRateModelField.BrokerID));
	RegField("CThostFtdcQryCommRateModelField","手续费率模板代码","TThostFtdcInvestorIDType", "CommModelID", &(m_ThostFtdcQryCommRateModelField.CommModelID));

	RegField("CThostFtdcMarginModelField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcMarginModelField.BrokerID));
	RegField("CThostFtdcMarginModelField","保证金率模板代码","TThostFtdcInvestorIDType", "MarginModelID", &(m_ThostFtdcMarginModelField.MarginModelID));
	RegField("CThostFtdcMarginModelField","模板名称","TThostFtdcCommModelNameType", "MarginModelName", &(m_ThostFtdcMarginModelField.MarginModelName));

	RegField("CThostFtdcQryMarginModelField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryMarginModelField.BrokerID));
	RegField("CThostFtdcQryMarginModelField","保证金率模板代码","TThostFtdcInvestorIDType", "MarginModelID", &(m_ThostFtdcQryMarginModelField.MarginModelID));

	RegField("CThostFtdcEWarrantOffsetField","交易日期","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcEWarrantOffsetField.TradingDay));
	RegField("CThostFtdcEWarrantOffsetField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcEWarrantOffsetField.BrokerID));
	RegField("CThostFtdcEWarrantOffsetField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcEWarrantOffsetField.InvestorID));
	RegField("CThostFtdcEWarrantOffsetField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcEWarrantOffsetField.ExchangeID));
	RegField("CThostFtdcEWarrantOffsetField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcEWarrantOffsetField.InstrumentID));
	RegField("CThostFtdcEWarrantOffsetField","买卖方向","TThostFtdcDirectionType", "Direction", &(m_ThostFtdcEWarrantOffsetField.Direction));
	RegField("CThostFtdcEWarrantOffsetField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcEWarrantOffsetField.HedgeFlag));
	RegField("CThostFtdcEWarrantOffsetField","数量","TThostFtdcVolumeType", "Volume", &(m_ThostFtdcEWarrantOffsetField.Volume));

	RegField("CThostFtdcQryEWarrantOffsetField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryEWarrantOffsetField.BrokerID));
	RegField("CThostFtdcQryEWarrantOffsetField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryEWarrantOffsetField.InvestorID));
	RegField("CThostFtdcQryEWarrantOffsetField","交易所代码","TThostFtdcExchangeIDType", "ExchangeID", &(m_ThostFtdcQryEWarrantOffsetField.ExchangeID));
	RegField("CThostFtdcQryEWarrantOffsetField","合约代码","TThostFtdcInstrumentIDType", "InstrumentID", &(m_ThostFtdcQryEWarrantOffsetField.InstrumentID));

	RegField("CThostFtdcQryInvestorProductGroupMarginField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryInvestorProductGroupMarginField.BrokerID));
	RegField("CThostFtdcQryInvestorProductGroupMarginField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcQryInvestorProductGroupMarginField.InvestorID));
	RegField("CThostFtdcQryInvestorProductGroupMarginField","品种/跨品种标示","TThostFtdcInstrumentIDType", "ProductGroupID", &(m_ThostFtdcQryInvestorProductGroupMarginField.ProductGroupID));
	RegField("CThostFtdcQryInvestorProductGroupMarginField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcQryInvestorProductGroupMarginField.HedgeFlag));

	RegField("CThostFtdcInvestorProductGroupMarginField","品种/跨品种标示","TThostFtdcInstrumentIDType", "ProductGroupID", &(m_ThostFtdcInvestorProductGroupMarginField.ProductGroupID));
	RegField("CThostFtdcInvestorProductGroupMarginField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcInvestorProductGroupMarginField.BrokerID));
	RegField("CThostFtdcInvestorProductGroupMarginField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcInvestorProductGroupMarginField.InvestorID));
	RegField("CThostFtdcInvestorProductGroupMarginField","交易日","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcInvestorProductGroupMarginField.TradingDay));
	RegField("CThostFtdcInvestorProductGroupMarginField","结算编号","TThostFtdcSettlementIDType", "SettlementID", &(m_ThostFtdcInvestorProductGroupMarginField.SettlementID));
	RegField("CThostFtdcInvestorProductGroupMarginField","冻结的保证金","TThostFtdcMoneyType", "FrozenMargin", &(m_ThostFtdcInvestorProductGroupMarginField.FrozenMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","多头冻结的保证金","TThostFtdcMoneyType", "LongFrozenMargin", &(m_ThostFtdcInvestorProductGroupMarginField.LongFrozenMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","空头冻结的保证金","TThostFtdcMoneyType", "ShortFrozenMargin", &(m_ThostFtdcInvestorProductGroupMarginField.ShortFrozenMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","占用的保证金","TThostFtdcMoneyType", "UseMargin", &(m_ThostFtdcInvestorProductGroupMarginField.UseMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","多头保证金","TThostFtdcMoneyType", "LongUseMargin", &(m_ThostFtdcInvestorProductGroupMarginField.LongUseMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","空头保证金","TThostFtdcMoneyType", "ShortUseMargin", &(m_ThostFtdcInvestorProductGroupMarginField.ShortUseMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","交易所保证金","TThostFtdcMoneyType", "ExchMargin", &(m_ThostFtdcInvestorProductGroupMarginField.ExchMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","交易所多头保证金","TThostFtdcMoneyType", "LongExchMargin", &(m_ThostFtdcInvestorProductGroupMarginField.LongExchMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","交易所空头保证金","TThostFtdcMoneyType", "ShortExchMargin", &(m_ThostFtdcInvestorProductGroupMarginField.ShortExchMargin));
	RegField("CThostFtdcInvestorProductGroupMarginField","平仓盈亏","TThostFtdcMoneyType", "CloseProfit", &(m_ThostFtdcInvestorProductGroupMarginField.CloseProfit));
	RegField("CThostFtdcInvestorProductGroupMarginField","冻结的手续费","TThostFtdcMoneyType", "FrozenCommission", &(m_ThostFtdcInvestorProductGroupMarginField.FrozenCommission));
	RegField("CThostFtdcInvestorProductGroupMarginField","手续费","TThostFtdcMoneyType", "Commission", &(m_ThostFtdcInvestorProductGroupMarginField.Commission));
	RegField("CThostFtdcInvestorProductGroupMarginField","冻结的资金","TThostFtdcMoneyType", "FrozenCash", &(m_ThostFtdcInvestorProductGroupMarginField.FrozenCash));
	RegField("CThostFtdcInvestorProductGroupMarginField","资金差额","TThostFtdcMoneyType", "CashIn", &(m_ThostFtdcInvestorProductGroupMarginField.CashIn));
	RegField("CThostFtdcInvestorProductGroupMarginField","持仓盈亏","TThostFtdcMoneyType", "PositionProfit", &(m_ThostFtdcInvestorProductGroupMarginField.PositionProfit));
	RegField("CThostFtdcInvestorProductGroupMarginField","折抵总金额","TThostFtdcMoneyType", "OffsetAmount", &(m_ThostFtdcInvestorProductGroupMarginField.OffsetAmount));
	RegField("CThostFtdcInvestorProductGroupMarginField","多头折抵总金额","TThostFtdcMoneyType", "LongOffsetAmount", &(m_ThostFtdcInvestorProductGroupMarginField.LongOffsetAmount));
	RegField("CThostFtdcInvestorProductGroupMarginField","空头折抵总金额","TThostFtdcMoneyType", "ShortOffsetAmount", &(m_ThostFtdcInvestorProductGroupMarginField.ShortOffsetAmount));
	RegField("CThostFtdcInvestorProductGroupMarginField","交易所折抵总金额","TThostFtdcMoneyType", "ExchOffsetAmount", &(m_ThostFtdcInvestorProductGroupMarginField.ExchOffsetAmount));
	RegField("CThostFtdcInvestorProductGroupMarginField","交易所多头折抵总金额","TThostFtdcMoneyType", "LongExchOffsetAmount", &(m_ThostFtdcInvestorProductGroupMarginField.LongExchOffsetAmount));
	RegField("CThostFtdcInvestorProductGroupMarginField","交易所空头折抵总金额","TThostFtdcMoneyType", "ShortExchOffsetAmount", &(m_ThostFtdcInvestorProductGroupMarginField.ShortExchOffsetAmount));
	RegField("CThostFtdcInvestorProductGroupMarginField","投机套保标志","TThostFtdcHedgeFlagType", "HedgeFlag", &(m_ThostFtdcInvestorProductGroupMarginField.HedgeFlag));

	RegField("CThostFtdcReqOpenAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqOpenAccountField.TradeCode));
	RegField("CThostFtdcReqOpenAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqOpenAccountField.BankID));
	RegField("CThostFtdcReqOpenAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqOpenAccountField.BankBranchID));
	RegField("CThostFtdcReqOpenAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqOpenAccountField.BrokerID));
	RegField("CThostFtdcReqOpenAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqOpenAccountField.BrokerBranchID));
	RegField("CThostFtdcReqOpenAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqOpenAccountField.TradeDate));
	RegField("CThostFtdcReqOpenAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqOpenAccountField.TradeTime));
	RegField("CThostFtdcReqOpenAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqOpenAccountField.BankSerial));
	RegField("CThostFtdcReqOpenAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqOpenAccountField.TradingDay));
	RegField("CThostFtdcReqOpenAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqOpenAccountField.PlateSerial));
	RegField("CThostFtdcReqOpenAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqOpenAccountField.LastFragment));
	RegField("CThostFtdcReqOpenAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqOpenAccountField.SessionID));
	RegField("CThostFtdcReqOpenAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcReqOpenAccountField.CustomerName));
	RegField("CThostFtdcReqOpenAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcReqOpenAccountField.IdCardType));
	RegField("CThostFtdcReqOpenAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcReqOpenAccountField.IdentifiedCardNo));
	RegField("CThostFtdcReqOpenAccountField","性别","TThostFtdcGenderType", "Gender", &(m_ThostFtdcReqOpenAccountField.Gender));
	RegField("CThostFtdcReqOpenAccountField","国家代码","TThostFtdcCountryCodeType", "CountryCode", &(m_ThostFtdcReqOpenAccountField.CountryCode));
	RegField("CThostFtdcReqOpenAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcReqOpenAccountField.CustType));
	RegField("CThostFtdcReqOpenAccountField","地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcReqOpenAccountField.Address));
	RegField("CThostFtdcReqOpenAccountField","邮编","TThostFtdcZipCodeType", "ZipCode", &(m_ThostFtdcReqOpenAccountField.ZipCode));
	RegField("CThostFtdcReqOpenAccountField","电话号码","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcReqOpenAccountField.Telephone));
	RegField("CThostFtdcReqOpenAccountField","手机","TThostFtdcMobilePhoneType", "MobilePhone", &(m_ThostFtdcReqOpenAccountField.MobilePhone));
	RegField("CThostFtdcReqOpenAccountField","传真","TThostFtdcFaxType", "Fax", &(m_ThostFtdcReqOpenAccountField.Fax));
	RegField("CThostFtdcReqOpenAccountField","电子邮件","TThostFtdcEMailType", "EMail", &(m_ThostFtdcReqOpenAccountField.EMail));
	RegField("CThostFtdcReqOpenAccountField","资金账户状态","TThostFtdcMoneyAccountStatusType", "MoneyAccountStatus", &(m_ThostFtdcReqOpenAccountField.MoneyAccountStatus));
	RegField("CThostFtdcReqOpenAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcReqOpenAccountField.BankAccount));
	RegField("CThostFtdcReqOpenAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcReqOpenAccountField.BankPassWord));
	RegField("CThostFtdcReqOpenAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcReqOpenAccountField.AccountID));
	RegField("CThostFtdcReqOpenAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqOpenAccountField.Password));
	RegField("CThostFtdcReqOpenAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqOpenAccountField.InstallID));
	RegField("CThostFtdcReqOpenAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcReqOpenAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcReqOpenAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqOpenAccountField.CurrencyID));
	RegField("CThostFtdcReqOpenAccountField","汇钞标志","TThostFtdcCashExchangeCodeType", "CashExchangeCode", &(m_ThostFtdcReqOpenAccountField.CashExchangeCode));
	RegField("CThostFtdcReqOpenAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqOpenAccountField.Digest));
	RegField("CThostFtdcReqOpenAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcReqOpenAccountField.BankAccType));
	RegField("CThostFtdcReqOpenAccountField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcReqOpenAccountField.DeviceID));
	RegField("CThostFtdcReqOpenAccountField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcReqOpenAccountField.BankSecuAccType));
	RegField("CThostFtdcReqOpenAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqOpenAccountField.BrokerIDByBank));
	RegField("CThostFtdcReqOpenAccountField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcReqOpenAccountField.BankSecuAcc));
	RegField("CThostFtdcReqOpenAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcReqOpenAccountField.BankPwdFlag));
	RegField("CThostFtdcReqOpenAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcReqOpenAccountField.SecuPwdFlag));
	RegField("CThostFtdcReqOpenAccountField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcReqOpenAccountField.OperNo));
	RegField("CThostFtdcReqOpenAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqOpenAccountField.TID));
	RegField("CThostFtdcReqOpenAccountField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqOpenAccountField.UserID));

	RegField("CThostFtdcReqCancelAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqCancelAccountField.TradeCode));
	RegField("CThostFtdcReqCancelAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqCancelAccountField.BankID));
	RegField("CThostFtdcReqCancelAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqCancelAccountField.BankBranchID));
	RegField("CThostFtdcReqCancelAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqCancelAccountField.BrokerID));
	RegField("CThostFtdcReqCancelAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqCancelAccountField.BrokerBranchID));
	RegField("CThostFtdcReqCancelAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqCancelAccountField.TradeDate));
	RegField("CThostFtdcReqCancelAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqCancelAccountField.TradeTime));
	RegField("CThostFtdcReqCancelAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqCancelAccountField.BankSerial));
	RegField("CThostFtdcReqCancelAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqCancelAccountField.TradingDay));
	RegField("CThostFtdcReqCancelAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqCancelAccountField.PlateSerial));
	RegField("CThostFtdcReqCancelAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqCancelAccountField.LastFragment));
	RegField("CThostFtdcReqCancelAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqCancelAccountField.SessionID));
	RegField("CThostFtdcReqCancelAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcReqCancelAccountField.CustomerName));
	RegField("CThostFtdcReqCancelAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcReqCancelAccountField.IdCardType));
	RegField("CThostFtdcReqCancelAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcReqCancelAccountField.IdentifiedCardNo));
	RegField("CThostFtdcReqCancelAccountField","性别","TThostFtdcGenderType", "Gender", &(m_ThostFtdcReqCancelAccountField.Gender));
	RegField("CThostFtdcReqCancelAccountField","国家代码","TThostFtdcCountryCodeType", "CountryCode", &(m_ThostFtdcReqCancelAccountField.CountryCode));
	RegField("CThostFtdcReqCancelAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcReqCancelAccountField.CustType));
	RegField("CThostFtdcReqCancelAccountField","地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcReqCancelAccountField.Address));
	RegField("CThostFtdcReqCancelAccountField","邮编","TThostFtdcZipCodeType", "ZipCode", &(m_ThostFtdcReqCancelAccountField.ZipCode));
	RegField("CThostFtdcReqCancelAccountField","电话号码","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcReqCancelAccountField.Telephone));
	RegField("CThostFtdcReqCancelAccountField","手机","TThostFtdcMobilePhoneType", "MobilePhone", &(m_ThostFtdcReqCancelAccountField.MobilePhone));
	RegField("CThostFtdcReqCancelAccountField","传真","TThostFtdcFaxType", "Fax", &(m_ThostFtdcReqCancelAccountField.Fax));
	RegField("CThostFtdcReqCancelAccountField","电子邮件","TThostFtdcEMailType", "EMail", &(m_ThostFtdcReqCancelAccountField.EMail));
	RegField("CThostFtdcReqCancelAccountField","资金账户状态","TThostFtdcMoneyAccountStatusType", "MoneyAccountStatus", &(m_ThostFtdcReqCancelAccountField.MoneyAccountStatus));
	RegField("CThostFtdcReqCancelAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcReqCancelAccountField.BankAccount));
	RegField("CThostFtdcReqCancelAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcReqCancelAccountField.BankPassWord));
	RegField("CThostFtdcReqCancelAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcReqCancelAccountField.AccountID));
	RegField("CThostFtdcReqCancelAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqCancelAccountField.Password));
	RegField("CThostFtdcReqCancelAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqCancelAccountField.InstallID));
	RegField("CThostFtdcReqCancelAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcReqCancelAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcReqCancelAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqCancelAccountField.CurrencyID));
	RegField("CThostFtdcReqCancelAccountField","汇钞标志","TThostFtdcCashExchangeCodeType", "CashExchangeCode", &(m_ThostFtdcReqCancelAccountField.CashExchangeCode));
	RegField("CThostFtdcReqCancelAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqCancelAccountField.Digest));
	RegField("CThostFtdcReqCancelAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcReqCancelAccountField.BankAccType));
	RegField("CThostFtdcReqCancelAccountField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcReqCancelAccountField.DeviceID));
	RegField("CThostFtdcReqCancelAccountField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcReqCancelAccountField.BankSecuAccType));
	RegField("CThostFtdcReqCancelAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqCancelAccountField.BrokerIDByBank));
	RegField("CThostFtdcReqCancelAccountField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcReqCancelAccountField.BankSecuAcc));
	RegField("CThostFtdcReqCancelAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcReqCancelAccountField.BankPwdFlag));
	RegField("CThostFtdcReqCancelAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcReqCancelAccountField.SecuPwdFlag));
	RegField("CThostFtdcReqCancelAccountField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcReqCancelAccountField.OperNo));
	RegField("CThostFtdcReqCancelAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqCancelAccountField.TID));
	RegField("CThostFtdcReqCancelAccountField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqCancelAccountField.UserID));

	RegField("CThostFtdcReqChangeAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqChangeAccountField.TradeCode));
	RegField("CThostFtdcReqChangeAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqChangeAccountField.BankID));
	RegField("CThostFtdcReqChangeAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqChangeAccountField.BankBranchID));
	RegField("CThostFtdcReqChangeAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqChangeAccountField.BrokerID));
	RegField("CThostFtdcReqChangeAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqChangeAccountField.BrokerBranchID));
	RegField("CThostFtdcReqChangeAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqChangeAccountField.TradeDate));
	RegField("CThostFtdcReqChangeAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqChangeAccountField.TradeTime));
	RegField("CThostFtdcReqChangeAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqChangeAccountField.BankSerial));
	RegField("CThostFtdcReqChangeAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqChangeAccountField.TradingDay));
	RegField("CThostFtdcReqChangeAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqChangeAccountField.PlateSerial));
	RegField("CThostFtdcReqChangeAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqChangeAccountField.LastFragment));
	RegField("CThostFtdcReqChangeAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqChangeAccountField.SessionID));
	RegField("CThostFtdcReqChangeAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcReqChangeAccountField.CustomerName));
	RegField("CThostFtdcReqChangeAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcReqChangeAccountField.IdCardType));
	RegField("CThostFtdcReqChangeAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcReqChangeAccountField.IdentifiedCardNo));
	RegField("CThostFtdcReqChangeAccountField","性别","TThostFtdcGenderType", "Gender", &(m_ThostFtdcReqChangeAccountField.Gender));
	RegField("CThostFtdcReqChangeAccountField","国家代码","TThostFtdcCountryCodeType", "CountryCode", &(m_ThostFtdcReqChangeAccountField.CountryCode));
	RegField("CThostFtdcReqChangeAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcReqChangeAccountField.CustType));
	RegField("CThostFtdcReqChangeAccountField","地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcReqChangeAccountField.Address));
	RegField("CThostFtdcReqChangeAccountField","邮编","TThostFtdcZipCodeType", "ZipCode", &(m_ThostFtdcReqChangeAccountField.ZipCode));
	RegField("CThostFtdcReqChangeAccountField","电话号码","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcReqChangeAccountField.Telephone));
	RegField("CThostFtdcReqChangeAccountField","手机","TThostFtdcMobilePhoneType", "MobilePhone", &(m_ThostFtdcReqChangeAccountField.MobilePhone));
	RegField("CThostFtdcReqChangeAccountField","传真","TThostFtdcFaxType", "Fax", &(m_ThostFtdcReqChangeAccountField.Fax));
	RegField("CThostFtdcReqChangeAccountField","电子邮件","TThostFtdcEMailType", "EMail", &(m_ThostFtdcReqChangeAccountField.EMail));
	RegField("CThostFtdcReqChangeAccountField","资金账户状态","TThostFtdcMoneyAccountStatusType", "MoneyAccountStatus", &(m_ThostFtdcReqChangeAccountField.MoneyAccountStatus));
	RegField("CThostFtdcReqChangeAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcReqChangeAccountField.BankAccount));
	RegField("CThostFtdcReqChangeAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcReqChangeAccountField.BankPassWord));
	RegField("CThostFtdcReqChangeAccountField","新银行帐号","TThostFtdcBankAccountType", "NewBankAccount", &(m_ThostFtdcReqChangeAccountField.NewBankAccount));
	RegField("CThostFtdcReqChangeAccountField","新银行密码","TThostFtdcPasswordType", "NewBankPassWord", &(m_ThostFtdcReqChangeAccountField.NewBankPassWord));
	RegField("CThostFtdcReqChangeAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcReqChangeAccountField.AccountID));
	RegField("CThostFtdcReqChangeAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqChangeAccountField.Password));
	RegField("CThostFtdcReqChangeAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcReqChangeAccountField.BankAccType));
	RegField("CThostFtdcReqChangeAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqChangeAccountField.InstallID));
	RegField("CThostFtdcReqChangeAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcReqChangeAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcReqChangeAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqChangeAccountField.CurrencyID));
	RegField("CThostFtdcReqChangeAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqChangeAccountField.BrokerIDByBank));
	RegField("CThostFtdcReqChangeAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcReqChangeAccountField.BankPwdFlag));
	RegField("CThostFtdcReqChangeAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcReqChangeAccountField.SecuPwdFlag));
	RegField("CThostFtdcReqChangeAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqChangeAccountField.TID));
	RegField("CThostFtdcReqChangeAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqChangeAccountField.Digest));

	RegField("CThostFtdcReqTransferField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqTransferField.TradeCode));
	RegField("CThostFtdcReqTransferField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqTransferField.BankID));
	RegField("CThostFtdcReqTransferField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqTransferField.BankBranchID));
	RegField("CThostFtdcReqTransferField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqTransferField.BrokerID));
	RegField("CThostFtdcReqTransferField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqTransferField.BrokerBranchID));
	RegField("CThostFtdcReqTransferField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqTransferField.TradeDate));
	RegField("CThostFtdcReqTransferField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqTransferField.TradeTime));
	RegField("CThostFtdcReqTransferField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqTransferField.BankSerial));
	RegField("CThostFtdcReqTransferField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqTransferField.TradingDay));
	RegField("CThostFtdcReqTransferField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqTransferField.PlateSerial));
	RegField("CThostFtdcReqTransferField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqTransferField.LastFragment));
	RegField("CThostFtdcReqTransferField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqTransferField.SessionID));
	RegField("CThostFtdcReqTransferField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcReqTransferField.CustomerName));
	RegField("CThostFtdcReqTransferField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcReqTransferField.IdCardType));
	RegField("CThostFtdcReqTransferField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcReqTransferField.IdentifiedCardNo));
	RegField("CThostFtdcReqTransferField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcReqTransferField.CustType));
	RegField("CThostFtdcReqTransferField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcReqTransferField.BankAccount));
	RegField("CThostFtdcReqTransferField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcReqTransferField.BankPassWord));
	RegField("CThostFtdcReqTransferField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcReqTransferField.AccountID));
	RegField("CThostFtdcReqTransferField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqTransferField.Password));
	RegField("CThostFtdcReqTransferField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqTransferField.InstallID));
	RegField("CThostFtdcReqTransferField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcReqTransferField.FutureSerial));
	RegField("CThostFtdcReqTransferField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqTransferField.UserID));
	RegField("CThostFtdcReqTransferField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcReqTransferField.VerifyCertNoFlag));
	RegField("CThostFtdcReqTransferField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqTransferField.CurrencyID));
	RegField("CThostFtdcReqTransferField","转帐金额","TThostFtdcTradeAmountType", "TradeAmount", &(m_ThostFtdcReqTransferField.TradeAmount));
	RegField("CThostFtdcReqTransferField","期货可取金额","TThostFtdcTradeAmountType", "FutureFetchAmount", &(m_ThostFtdcReqTransferField.FutureFetchAmount));
	RegField("CThostFtdcReqTransferField","费用支付标志","TThostFtdcFeePayFlagType", "FeePayFlag", &(m_ThostFtdcReqTransferField.FeePayFlag));
	RegField("CThostFtdcReqTransferField","应收客户费用","TThostFtdcCustFeeType", "CustFee", &(m_ThostFtdcReqTransferField.CustFee));
	RegField("CThostFtdcReqTransferField","应收期货公司费用","TThostFtdcFutureFeeType", "BrokerFee", &(m_ThostFtdcReqTransferField.BrokerFee));
	RegField("CThostFtdcReqTransferField","发送方给接收方的消息","TThostFtdcAddInfoType", "Message", &(m_ThostFtdcReqTransferField.Message));
	RegField("CThostFtdcReqTransferField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqTransferField.Digest));
	RegField("CThostFtdcReqTransferField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcReqTransferField.BankAccType));
	RegField("CThostFtdcReqTransferField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcReqTransferField.DeviceID));
	RegField("CThostFtdcReqTransferField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcReqTransferField.BankSecuAccType));
	RegField("CThostFtdcReqTransferField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqTransferField.BrokerIDByBank));
	RegField("CThostFtdcReqTransferField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcReqTransferField.BankSecuAcc));
	RegField("CThostFtdcReqTransferField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcReqTransferField.BankPwdFlag));
	RegField("CThostFtdcReqTransferField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcReqTransferField.SecuPwdFlag));
	RegField("CThostFtdcReqTransferField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcReqTransferField.OperNo));
	RegField("CThostFtdcReqTransferField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcReqTransferField.RequestID));
	RegField("CThostFtdcReqTransferField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqTransferField.TID));
	RegField("CThostFtdcReqTransferField","转账交易状态","TThostFtdcTransferStatusType", "TransferStatus", &(m_ThostFtdcReqTransferField.TransferStatus));

	RegField("CThostFtdcRspTransferField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcRspTransferField.TradeCode));
	RegField("CThostFtdcRspTransferField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcRspTransferField.BankID));
	RegField("CThostFtdcRspTransferField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcRspTransferField.BankBranchID));
	RegField("CThostFtdcRspTransferField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspTransferField.BrokerID));
	RegField("CThostFtdcRspTransferField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcRspTransferField.BrokerBranchID));
	RegField("CThostFtdcRspTransferField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcRspTransferField.TradeDate));
	RegField("CThostFtdcRspTransferField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcRspTransferField.TradeTime));
	RegField("CThostFtdcRspTransferField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcRspTransferField.BankSerial));
	RegField("CThostFtdcRspTransferField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcRspTransferField.TradingDay));
	RegField("CThostFtdcRspTransferField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcRspTransferField.PlateSerial));
	RegField("CThostFtdcRspTransferField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcRspTransferField.LastFragment));
	RegField("CThostFtdcRspTransferField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspTransferField.SessionID));
	RegField("CThostFtdcRspTransferField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcRspTransferField.CustomerName));
	RegField("CThostFtdcRspTransferField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcRspTransferField.IdCardType));
	RegField("CThostFtdcRspTransferField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcRspTransferField.IdentifiedCardNo));
	RegField("CThostFtdcRspTransferField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcRspTransferField.CustType));
	RegField("CThostFtdcRspTransferField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcRspTransferField.BankAccount));
	RegField("CThostFtdcRspTransferField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcRspTransferField.BankPassWord));
	RegField("CThostFtdcRspTransferField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcRspTransferField.AccountID));
	RegField("CThostFtdcRspTransferField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcRspTransferField.Password));
	RegField("CThostFtdcRspTransferField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcRspTransferField.InstallID));
	RegField("CThostFtdcRspTransferField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcRspTransferField.FutureSerial));
	RegField("CThostFtdcRspTransferField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspTransferField.UserID));
	RegField("CThostFtdcRspTransferField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcRspTransferField.VerifyCertNoFlag));
	RegField("CThostFtdcRspTransferField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcRspTransferField.CurrencyID));
	RegField("CThostFtdcRspTransferField","转帐金额","TThostFtdcTradeAmountType", "TradeAmount", &(m_ThostFtdcRspTransferField.TradeAmount));
	RegField("CThostFtdcRspTransferField","期货可取金额","TThostFtdcTradeAmountType", "FutureFetchAmount", &(m_ThostFtdcRspTransferField.FutureFetchAmount));
	RegField("CThostFtdcRspTransferField","费用支付标志","TThostFtdcFeePayFlagType", "FeePayFlag", &(m_ThostFtdcRspTransferField.FeePayFlag));
	RegField("CThostFtdcRspTransferField","应收客户费用","TThostFtdcCustFeeType", "CustFee", &(m_ThostFtdcRspTransferField.CustFee));
	RegField("CThostFtdcRspTransferField","应收期货公司费用","TThostFtdcFutureFeeType", "BrokerFee", &(m_ThostFtdcRspTransferField.BrokerFee));
	RegField("CThostFtdcRspTransferField","发送方给接收方的消息","TThostFtdcAddInfoType", "Message", &(m_ThostFtdcRspTransferField.Message));
	RegField("CThostFtdcRspTransferField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcRspTransferField.Digest));
	RegField("CThostFtdcRspTransferField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcRspTransferField.BankAccType));
	RegField("CThostFtdcRspTransferField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcRspTransferField.DeviceID));
	RegField("CThostFtdcRspTransferField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcRspTransferField.BankSecuAccType));
	RegField("CThostFtdcRspTransferField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcRspTransferField.BrokerIDByBank));
	RegField("CThostFtdcRspTransferField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcRspTransferField.BankSecuAcc));
	RegField("CThostFtdcRspTransferField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcRspTransferField.BankPwdFlag));
	RegField("CThostFtdcRspTransferField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcRspTransferField.SecuPwdFlag));
	RegField("CThostFtdcRspTransferField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcRspTransferField.OperNo));
	RegField("CThostFtdcRspTransferField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcRspTransferField.RequestID));
	RegField("CThostFtdcRspTransferField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcRspTransferField.TID));
	RegField("CThostFtdcRspTransferField","转账交易状态","TThostFtdcTransferStatusType", "TransferStatus", &(m_ThostFtdcRspTransferField.TransferStatus));
	RegField("CThostFtdcRspTransferField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcRspTransferField.ErrorID));
	RegField("CThostFtdcRspTransferField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcRspTransferField.ErrorMsg));

	RegField("CThostFtdcReqRepealField","冲正时间间隔","TThostFtdcRepealTimeIntervalType", "RepealTimeInterval", &(m_ThostFtdcReqRepealField.RepealTimeInterval));
	RegField("CThostFtdcReqRepealField","已经冲正次数","TThostFtdcRepealedTimesType", "RepealedTimes", &(m_ThostFtdcReqRepealField.RepealedTimes));
	RegField("CThostFtdcReqRepealField","银行冲正标志","TThostFtdcBankRepealFlagType", "BankRepealFlag", &(m_ThostFtdcReqRepealField.BankRepealFlag));
	RegField("CThostFtdcReqRepealField","期商冲正标志","TThostFtdcBrokerRepealFlagType", "BrokerRepealFlag", &(m_ThostFtdcReqRepealField.BrokerRepealFlag));
	RegField("CThostFtdcReqRepealField","被冲正平台流水号","TThostFtdcPlateSerialType", "PlateRepealSerial", &(m_ThostFtdcReqRepealField.PlateRepealSerial));
	RegField("CThostFtdcReqRepealField","被冲正银行流水号","TThostFtdcBankSerialType", "BankRepealSerial", &(m_ThostFtdcReqRepealField.BankRepealSerial));
	RegField("CThostFtdcReqRepealField","被冲正期货流水号","TThostFtdcFutureSerialType", "FutureRepealSerial", &(m_ThostFtdcReqRepealField.FutureRepealSerial));
	RegField("CThostFtdcReqRepealField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqRepealField.TradeCode));
	RegField("CThostFtdcReqRepealField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqRepealField.BankID));
	RegField("CThostFtdcReqRepealField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqRepealField.BankBranchID));
	RegField("CThostFtdcReqRepealField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqRepealField.BrokerID));
	RegField("CThostFtdcReqRepealField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqRepealField.BrokerBranchID));
	RegField("CThostFtdcReqRepealField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqRepealField.TradeDate));
	RegField("CThostFtdcReqRepealField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqRepealField.TradeTime));
	RegField("CThostFtdcReqRepealField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqRepealField.BankSerial));
	RegField("CThostFtdcReqRepealField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqRepealField.TradingDay));
	RegField("CThostFtdcReqRepealField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqRepealField.PlateSerial));
	RegField("CThostFtdcReqRepealField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqRepealField.LastFragment));
	RegField("CThostFtdcReqRepealField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqRepealField.SessionID));
	RegField("CThostFtdcReqRepealField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcReqRepealField.CustomerName));
	RegField("CThostFtdcReqRepealField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcReqRepealField.IdCardType));
	RegField("CThostFtdcReqRepealField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcReqRepealField.IdentifiedCardNo));
	RegField("CThostFtdcReqRepealField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcReqRepealField.CustType));
	RegField("CThostFtdcReqRepealField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcReqRepealField.BankAccount));
	RegField("CThostFtdcReqRepealField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcReqRepealField.BankPassWord));
	RegField("CThostFtdcReqRepealField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcReqRepealField.AccountID));
	RegField("CThostFtdcReqRepealField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqRepealField.Password));
	RegField("CThostFtdcReqRepealField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqRepealField.InstallID));
	RegField("CThostFtdcReqRepealField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcReqRepealField.FutureSerial));
	RegField("CThostFtdcReqRepealField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqRepealField.UserID));
	RegField("CThostFtdcReqRepealField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcReqRepealField.VerifyCertNoFlag));
	RegField("CThostFtdcReqRepealField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqRepealField.CurrencyID));
	RegField("CThostFtdcReqRepealField","转帐金额","TThostFtdcTradeAmountType", "TradeAmount", &(m_ThostFtdcReqRepealField.TradeAmount));
	RegField("CThostFtdcReqRepealField","期货可取金额","TThostFtdcTradeAmountType", "FutureFetchAmount", &(m_ThostFtdcReqRepealField.FutureFetchAmount));
	RegField("CThostFtdcReqRepealField","费用支付标志","TThostFtdcFeePayFlagType", "FeePayFlag", &(m_ThostFtdcReqRepealField.FeePayFlag));
	RegField("CThostFtdcReqRepealField","应收客户费用","TThostFtdcCustFeeType", "CustFee", &(m_ThostFtdcReqRepealField.CustFee));
	RegField("CThostFtdcReqRepealField","应收期货公司费用","TThostFtdcFutureFeeType", "BrokerFee", &(m_ThostFtdcReqRepealField.BrokerFee));
	RegField("CThostFtdcReqRepealField","发送方给接收方的消息","TThostFtdcAddInfoType", "Message", &(m_ThostFtdcReqRepealField.Message));
	RegField("CThostFtdcReqRepealField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqRepealField.Digest));
	RegField("CThostFtdcReqRepealField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcReqRepealField.BankAccType));
	RegField("CThostFtdcReqRepealField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcReqRepealField.DeviceID));
	RegField("CThostFtdcReqRepealField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcReqRepealField.BankSecuAccType));
	RegField("CThostFtdcReqRepealField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqRepealField.BrokerIDByBank));
	RegField("CThostFtdcReqRepealField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcReqRepealField.BankSecuAcc));
	RegField("CThostFtdcReqRepealField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcReqRepealField.BankPwdFlag));
	RegField("CThostFtdcReqRepealField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcReqRepealField.SecuPwdFlag));
	RegField("CThostFtdcReqRepealField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcReqRepealField.OperNo));
	RegField("CThostFtdcReqRepealField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcReqRepealField.RequestID));
	RegField("CThostFtdcReqRepealField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqRepealField.TID));
	RegField("CThostFtdcReqRepealField","转账交易状态","TThostFtdcTransferStatusType", "TransferStatus", &(m_ThostFtdcReqRepealField.TransferStatus));

	RegField("CThostFtdcRspRepealField","冲正时间间隔","TThostFtdcRepealTimeIntervalType", "RepealTimeInterval", &(m_ThostFtdcRspRepealField.RepealTimeInterval));
	RegField("CThostFtdcRspRepealField","已经冲正次数","TThostFtdcRepealedTimesType", "RepealedTimes", &(m_ThostFtdcRspRepealField.RepealedTimes));
	RegField("CThostFtdcRspRepealField","银行冲正标志","TThostFtdcBankRepealFlagType", "BankRepealFlag", &(m_ThostFtdcRspRepealField.BankRepealFlag));
	RegField("CThostFtdcRspRepealField","期商冲正标志","TThostFtdcBrokerRepealFlagType", "BrokerRepealFlag", &(m_ThostFtdcRspRepealField.BrokerRepealFlag));
	RegField("CThostFtdcRspRepealField","被冲正平台流水号","TThostFtdcPlateSerialType", "PlateRepealSerial", &(m_ThostFtdcRspRepealField.PlateRepealSerial));
	RegField("CThostFtdcRspRepealField","被冲正银行流水号","TThostFtdcBankSerialType", "BankRepealSerial", &(m_ThostFtdcRspRepealField.BankRepealSerial));
	RegField("CThostFtdcRspRepealField","被冲正期货流水号","TThostFtdcFutureSerialType", "FutureRepealSerial", &(m_ThostFtdcRspRepealField.FutureRepealSerial));
	RegField("CThostFtdcRspRepealField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcRspRepealField.TradeCode));
	RegField("CThostFtdcRspRepealField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcRspRepealField.BankID));
	RegField("CThostFtdcRspRepealField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcRspRepealField.BankBranchID));
	RegField("CThostFtdcRspRepealField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspRepealField.BrokerID));
	RegField("CThostFtdcRspRepealField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcRspRepealField.BrokerBranchID));
	RegField("CThostFtdcRspRepealField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcRspRepealField.TradeDate));
	RegField("CThostFtdcRspRepealField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcRspRepealField.TradeTime));
	RegField("CThostFtdcRspRepealField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcRspRepealField.BankSerial));
	RegField("CThostFtdcRspRepealField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcRspRepealField.TradingDay));
	RegField("CThostFtdcRspRepealField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcRspRepealField.PlateSerial));
	RegField("CThostFtdcRspRepealField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcRspRepealField.LastFragment));
	RegField("CThostFtdcRspRepealField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspRepealField.SessionID));
	RegField("CThostFtdcRspRepealField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcRspRepealField.CustomerName));
	RegField("CThostFtdcRspRepealField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcRspRepealField.IdCardType));
	RegField("CThostFtdcRspRepealField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcRspRepealField.IdentifiedCardNo));
	RegField("CThostFtdcRspRepealField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcRspRepealField.CustType));
	RegField("CThostFtdcRspRepealField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcRspRepealField.BankAccount));
	RegField("CThostFtdcRspRepealField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcRspRepealField.BankPassWord));
	RegField("CThostFtdcRspRepealField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcRspRepealField.AccountID));
	RegField("CThostFtdcRspRepealField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcRspRepealField.Password));
	RegField("CThostFtdcRspRepealField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcRspRepealField.InstallID));
	RegField("CThostFtdcRspRepealField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcRspRepealField.FutureSerial));
	RegField("CThostFtdcRspRepealField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspRepealField.UserID));
	RegField("CThostFtdcRspRepealField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcRspRepealField.VerifyCertNoFlag));
	RegField("CThostFtdcRspRepealField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcRspRepealField.CurrencyID));
	RegField("CThostFtdcRspRepealField","转帐金额","TThostFtdcTradeAmountType", "TradeAmount", &(m_ThostFtdcRspRepealField.TradeAmount));
	RegField("CThostFtdcRspRepealField","期货可取金额","TThostFtdcTradeAmountType", "FutureFetchAmount", &(m_ThostFtdcRspRepealField.FutureFetchAmount));
	RegField("CThostFtdcRspRepealField","费用支付标志","TThostFtdcFeePayFlagType", "FeePayFlag", &(m_ThostFtdcRspRepealField.FeePayFlag));
	RegField("CThostFtdcRspRepealField","应收客户费用","TThostFtdcCustFeeType", "CustFee", &(m_ThostFtdcRspRepealField.CustFee));
	RegField("CThostFtdcRspRepealField","应收期货公司费用","TThostFtdcFutureFeeType", "BrokerFee", &(m_ThostFtdcRspRepealField.BrokerFee));
	RegField("CThostFtdcRspRepealField","发送方给接收方的消息","TThostFtdcAddInfoType", "Message", &(m_ThostFtdcRspRepealField.Message));
	RegField("CThostFtdcRspRepealField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcRspRepealField.Digest));
	RegField("CThostFtdcRspRepealField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcRspRepealField.BankAccType));
	RegField("CThostFtdcRspRepealField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcRspRepealField.DeviceID));
	RegField("CThostFtdcRspRepealField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcRspRepealField.BankSecuAccType));
	RegField("CThostFtdcRspRepealField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcRspRepealField.BrokerIDByBank));
	RegField("CThostFtdcRspRepealField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcRspRepealField.BankSecuAcc));
	RegField("CThostFtdcRspRepealField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcRspRepealField.BankPwdFlag));
	RegField("CThostFtdcRspRepealField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcRspRepealField.SecuPwdFlag));
	RegField("CThostFtdcRspRepealField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcRspRepealField.OperNo));
	RegField("CThostFtdcRspRepealField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcRspRepealField.RequestID));
	RegField("CThostFtdcRspRepealField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcRspRepealField.TID));
	RegField("CThostFtdcRspRepealField","转账交易状态","TThostFtdcTransferStatusType", "TransferStatus", &(m_ThostFtdcRspRepealField.TransferStatus));
	RegField("CThostFtdcRspRepealField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcRspRepealField.ErrorID));
	RegField("CThostFtdcRspRepealField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcRspRepealField.ErrorMsg));

	RegField("CThostFtdcReqQueryAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqQueryAccountField.TradeCode));
	RegField("CThostFtdcReqQueryAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqQueryAccountField.BankID));
	RegField("CThostFtdcReqQueryAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqQueryAccountField.BankBranchID));
	RegField("CThostFtdcReqQueryAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqQueryAccountField.BrokerID));
	RegField("CThostFtdcReqQueryAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqQueryAccountField.BrokerBranchID));
	RegField("CThostFtdcReqQueryAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqQueryAccountField.TradeDate));
	RegField("CThostFtdcReqQueryAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqQueryAccountField.TradeTime));
	RegField("CThostFtdcReqQueryAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqQueryAccountField.BankSerial));
	RegField("CThostFtdcReqQueryAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqQueryAccountField.TradingDay));
	RegField("CThostFtdcReqQueryAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqQueryAccountField.PlateSerial));
	RegField("CThostFtdcReqQueryAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqQueryAccountField.LastFragment));
	RegField("CThostFtdcReqQueryAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqQueryAccountField.SessionID));
	RegField("CThostFtdcReqQueryAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcReqQueryAccountField.CustomerName));
	RegField("CThostFtdcReqQueryAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcReqQueryAccountField.IdCardType));
	RegField("CThostFtdcReqQueryAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcReqQueryAccountField.IdentifiedCardNo));
	RegField("CThostFtdcReqQueryAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcReqQueryAccountField.CustType));
	RegField("CThostFtdcReqQueryAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcReqQueryAccountField.BankAccount));
	RegField("CThostFtdcReqQueryAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcReqQueryAccountField.BankPassWord));
	RegField("CThostFtdcReqQueryAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcReqQueryAccountField.AccountID));
	RegField("CThostFtdcReqQueryAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqQueryAccountField.Password));
	RegField("CThostFtdcReqQueryAccountField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcReqQueryAccountField.FutureSerial));
	RegField("CThostFtdcReqQueryAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqQueryAccountField.InstallID));
	RegField("CThostFtdcReqQueryAccountField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqQueryAccountField.UserID));
	RegField("CThostFtdcReqQueryAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcReqQueryAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcReqQueryAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqQueryAccountField.CurrencyID));
	RegField("CThostFtdcReqQueryAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqQueryAccountField.Digest));
	RegField("CThostFtdcReqQueryAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcReqQueryAccountField.BankAccType));
	RegField("CThostFtdcReqQueryAccountField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcReqQueryAccountField.DeviceID));
	RegField("CThostFtdcReqQueryAccountField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcReqQueryAccountField.BankSecuAccType));
	RegField("CThostFtdcReqQueryAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqQueryAccountField.BrokerIDByBank));
	RegField("CThostFtdcReqQueryAccountField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcReqQueryAccountField.BankSecuAcc));
	RegField("CThostFtdcReqQueryAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcReqQueryAccountField.BankPwdFlag));
	RegField("CThostFtdcReqQueryAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcReqQueryAccountField.SecuPwdFlag));
	RegField("CThostFtdcReqQueryAccountField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcReqQueryAccountField.OperNo));
	RegField("CThostFtdcReqQueryAccountField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcReqQueryAccountField.RequestID));
	RegField("CThostFtdcReqQueryAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqQueryAccountField.TID));

	RegField("CThostFtdcRspQueryAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcRspQueryAccountField.TradeCode));
	RegField("CThostFtdcRspQueryAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcRspQueryAccountField.BankID));
	RegField("CThostFtdcRspQueryAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcRspQueryAccountField.BankBranchID));
	RegField("CThostFtdcRspQueryAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspQueryAccountField.BrokerID));
	RegField("CThostFtdcRspQueryAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcRspQueryAccountField.BrokerBranchID));
	RegField("CThostFtdcRspQueryAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcRspQueryAccountField.TradeDate));
	RegField("CThostFtdcRspQueryAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcRspQueryAccountField.TradeTime));
	RegField("CThostFtdcRspQueryAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcRspQueryAccountField.BankSerial));
	RegField("CThostFtdcRspQueryAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcRspQueryAccountField.TradingDay));
	RegField("CThostFtdcRspQueryAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcRspQueryAccountField.PlateSerial));
	RegField("CThostFtdcRspQueryAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcRspQueryAccountField.LastFragment));
	RegField("CThostFtdcRspQueryAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspQueryAccountField.SessionID));
	RegField("CThostFtdcRspQueryAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcRspQueryAccountField.CustomerName));
	RegField("CThostFtdcRspQueryAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcRspQueryAccountField.IdCardType));
	RegField("CThostFtdcRspQueryAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcRspQueryAccountField.IdentifiedCardNo));
	RegField("CThostFtdcRspQueryAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcRspQueryAccountField.CustType));
	RegField("CThostFtdcRspQueryAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcRspQueryAccountField.BankAccount));
	RegField("CThostFtdcRspQueryAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcRspQueryAccountField.BankPassWord));
	RegField("CThostFtdcRspQueryAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcRspQueryAccountField.AccountID));
	RegField("CThostFtdcRspQueryAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcRspQueryAccountField.Password));
	RegField("CThostFtdcRspQueryAccountField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcRspQueryAccountField.FutureSerial));
	RegField("CThostFtdcRspQueryAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcRspQueryAccountField.InstallID));
	RegField("CThostFtdcRspQueryAccountField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspQueryAccountField.UserID));
	RegField("CThostFtdcRspQueryAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcRspQueryAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcRspQueryAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcRspQueryAccountField.CurrencyID));
	RegField("CThostFtdcRspQueryAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcRspQueryAccountField.Digest));
	RegField("CThostFtdcRspQueryAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcRspQueryAccountField.BankAccType));
	RegField("CThostFtdcRspQueryAccountField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcRspQueryAccountField.DeviceID));
	RegField("CThostFtdcRspQueryAccountField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcRspQueryAccountField.BankSecuAccType));
	RegField("CThostFtdcRspQueryAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcRspQueryAccountField.BrokerIDByBank));
	RegField("CThostFtdcRspQueryAccountField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcRspQueryAccountField.BankSecuAcc));
	RegField("CThostFtdcRspQueryAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcRspQueryAccountField.BankPwdFlag));
	RegField("CThostFtdcRspQueryAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcRspQueryAccountField.SecuPwdFlag));
	RegField("CThostFtdcRspQueryAccountField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcRspQueryAccountField.OperNo));
	RegField("CThostFtdcRspQueryAccountField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcRspQueryAccountField.RequestID));
	RegField("CThostFtdcRspQueryAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcRspQueryAccountField.TID));
	RegField("CThostFtdcRspQueryAccountField","银行可用金额","TThostFtdcTradeAmountType", "BankUseAmount", &(m_ThostFtdcRspQueryAccountField.BankUseAmount));
	RegField("CThostFtdcRspQueryAccountField","银行可取金额","TThostFtdcTradeAmountType", "BankFetchAmount", &(m_ThostFtdcRspQueryAccountField.BankFetchAmount));

	RegField("CThostFtdcFutureSignIOField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcFutureSignIOField.TradeCode));
	RegField("CThostFtdcFutureSignIOField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcFutureSignIOField.BankID));
	RegField("CThostFtdcFutureSignIOField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcFutureSignIOField.BankBranchID));
	RegField("CThostFtdcFutureSignIOField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcFutureSignIOField.BrokerID));
	RegField("CThostFtdcFutureSignIOField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcFutureSignIOField.BrokerBranchID));
	RegField("CThostFtdcFutureSignIOField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcFutureSignIOField.TradeDate));
	RegField("CThostFtdcFutureSignIOField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcFutureSignIOField.TradeTime));
	RegField("CThostFtdcFutureSignIOField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcFutureSignIOField.BankSerial));
	RegField("CThostFtdcFutureSignIOField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcFutureSignIOField.TradingDay));
	RegField("CThostFtdcFutureSignIOField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcFutureSignIOField.PlateSerial));
	RegField("CThostFtdcFutureSignIOField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcFutureSignIOField.LastFragment));
	RegField("CThostFtdcFutureSignIOField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcFutureSignIOField.SessionID));
	RegField("CThostFtdcFutureSignIOField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcFutureSignIOField.InstallID));
	RegField("CThostFtdcFutureSignIOField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcFutureSignIOField.UserID));
	RegField("CThostFtdcFutureSignIOField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcFutureSignIOField.Digest));
	RegField("CThostFtdcFutureSignIOField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcFutureSignIOField.CurrencyID));
	RegField("CThostFtdcFutureSignIOField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcFutureSignIOField.DeviceID));
	RegField("CThostFtdcFutureSignIOField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcFutureSignIOField.BrokerIDByBank));
	RegField("CThostFtdcFutureSignIOField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcFutureSignIOField.OperNo));
	RegField("CThostFtdcFutureSignIOField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcFutureSignIOField.RequestID));
	RegField("CThostFtdcFutureSignIOField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcFutureSignIOField.TID));

	RegField("CThostFtdcRspFutureSignInField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcRspFutureSignInField.TradeCode));
	RegField("CThostFtdcRspFutureSignInField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcRspFutureSignInField.BankID));
	RegField("CThostFtdcRspFutureSignInField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcRspFutureSignInField.BankBranchID));
	RegField("CThostFtdcRspFutureSignInField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspFutureSignInField.BrokerID));
	RegField("CThostFtdcRspFutureSignInField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcRspFutureSignInField.BrokerBranchID));
	RegField("CThostFtdcRspFutureSignInField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcRspFutureSignInField.TradeDate));
	RegField("CThostFtdcRspFutureSignInField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcRspFutureSignInField.TradeTime));
	RegField("CThostFtdcRspFutureSignInField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcRspFutureSignInField.BankSerial));
	RegField("CThostFtdcRspFutureSignInField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcRspFutureSignInField.TradingDay));
	RegField("CThostFtdcRspFutureSignInField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcRspFutureSignInField.PlateSerial));
	RegField("CThostFtdcRspFutureSignInField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcRspFutureSignInField.LastFragment));
	RegField("CThostFtdcRspFutureSignInField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspFutureSignInField.SessionID));
	RegField("CThostFtdcRspFutureSignInField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcRspFutureSignInField.InstallID));
	RegField("CThostFtdcRspFutureSignInField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspFutureSignInField.UserID));
	RegField("CThostFtdcRspFutureSignInField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcRspFutureSignInField.Digest));
	RegField("CThostFtdcRspFutureSignInField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcRspFutureSignInField.CurrencyID));
	RegField("CThostFtdcRspFutureSignInField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcRspFutureSignInField.DeviceID));
	RegField("CThostFtdcRspFutureSignInField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcRspFutureSignInField.BrokerIDByBank));
	RegField("CThostFtdcRspFutureSignInField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcRspFutureSignInField.OperNo));
	RegField("CThostFtdcRspFutureSignInField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcRspFutureSignInField.RequestID));
	RegField("CThostFtdcRspFutureSignInField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcRspFutureSignInField.TID));
	RegField("CThostFtdcRspFutureSignInField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcRspFutureSignInField.ErrorID));
	RegField("CThostFtdcRspFutureSignInField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcRspFutureSignInField.ErrorMsg));
	RegField("CThostFtdcRspFutureSignInField","PIN密钥","TThostFtdcPasswordKeyType", "PinKey", &(m_ThostFtdcRspFutureSignInField.PinKey));
	RegField("CThostFtdcRspFutureSignInField","MAC密钥","TThostFtdcPasswordKeyType", "MacKey", &(m_ThostFtdcRspFutureSignInField.MacKey));

	RegField("CThostFtdcReqFutureSignOutField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqFutureSignOutField.TradeCode));
	RegField("CThostFtdcReqFutureSignOutField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqFutureSignOutField.BankID));
	RegField("CThostFtdcReqFutureSignOutField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqFutureSignOutField.BankBranchID));
	RegField("CThostFtdcReqFutureSignOutField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqFutureSignOutField.BrokerID));
	RegField("CThostFtdcReqFutureSignOutField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqFutureSignOutField.BrokerBranchID));
	RegField("CThostFtdcReqFutureSignOutField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqFutureSignOutField.TradeDate));
	RegField("CThostFtdcReqFutureSignOutField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqFutureSignOutField.TradeTime));
	RegField("CThostFtdcReqFutureSignOutField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqFutureSignOutField.BankSerial));
	RegField("CThostFtdcReqFutureSignOutField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqFutureSignOutField.TradingDay));
	RegField("CThostFtdcReqFutureSignOutField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqFutureSignOutField.PlateSerial));
	RegField("CThostFtdcReqFutureSignOutField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqFutureSignOutField.LastFragment));
	RegField("CThostFtdcReqFutureSignOutField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqFutureSignOutField.SessionID));
	RegField("CThostFtdcReqFutureSignOutField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqFutureSignOutField.InstallID));
	RegField("CThostFtdcReqFutureSignOutField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqFutureSignOutField.UserID));
	RegField("CThostFtdcReqFutureSignOutField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqFutureSignOutField.Digest));
	RegField("CThostFtdcReqFutureSignOutField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqFutureSignOutField.CurrencyID));
	RegField("CThostFtdcReqFutureSignOutField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcReqFutureSignOutField.DeviceID));
	RegField("CThostFtdcReqFutureSignOutField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqFutureSignOutField.BrokerIDByBank));
	RegField("CThostFtdcReqFutureSignOutField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcReqFutureSignOutField.OperNo));
	RegField("CThostFtdcReqFutureSignOutField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcReqFutureSignOutField.RequestID));
	RegField("CThostFtdcReqFutureSignOutField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqFutureSignOutField.TID));

	RegField("CThostFtdcRspFutureSignOutField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcRspFutureSignOutField.TradeCode));
	RegField("CThostFtdcRspFutureSignOutField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcRspFutureSignOutField.BankID));
	RegField("CThostFtdcRspFutureSignOutField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcRspFutureSignOutField.BankBranchID));
	RegField("CThostFtdcRspFutureSignOutField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspFutureSignOutField.BrokerID));
	RegField("CThostFtdcRspFutureSignOutField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcRspFutureSignOutField.BrokerBranchID));
	RegField("CThostFtdcRspFutureSignOutField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcRspFutureSignOutField.TradeDate));
	RegField("CThostFtdcRspFutureSignOutField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcRspFutureSignOutField.TradeTime));
	RegField("CThostFtdcRspFutureSignOutField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcRspFutureSignOutField.BankSerial));
	RegField("CThostFtdcRspFutureSignOutField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcRspFutureSignOutField.TradingDay));
	RegField("CThostFtdcRspFutureSignOutField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcRspFutureSignOutField.PlateSerial));
	RegField("CThostFtdcRspFutureSignOutField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcRspFutureSignOutField.LastFragment));
	RegField("CThostFtdcRspFutureSignOutField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspFutureSignOutField.SessionID));
	RegField("CThostFtdcRspFutureSignOutField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcRspFutureSignOutField.InstallID));
	RegField("CThostFtdcRspFutureSignOutField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspFutureSignOutField.UserID));
	RegField("CThostFtdcRspFutureSignOutField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcRspFutureSignOutField.Digest));
	RegField("CThostFtdcRspFutureSignOutField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcRspFutureSignOutField.CurrencyID));
	RegField("CThostFtdcRspFutureSignOutField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcRspFutureSignOutField.DeviceID));
	RegField("CThostFtdcRspFutureSignOutField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcRspFutureSignOutField.BrokerIDByBank));
	RegField("CThostFtdcRspFutureSignOutField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcRspFutureSignOutField.OperNo));
	RegField("CThostFtdcRspFutureSignOutField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcRspFutureSignOutField.RequestID));
	RegField("CThostFtdcRspFutureSignOutField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcRspFutureSignOutField.TID));
	RegField("CThostFtdcRspFutureSignOutField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcRspFutureSignOutField.ErrorID));
	RegField("CThostFtdcRspFutureSignOutField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcRspFutureSignOutField.ErrorMsg));

	RegField("CThostFtdcReqQueryTradeResultBySerialField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqQueryTradeResultBySerialField.TradeCode));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqQueryTradeResultBySerialField.BankID));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqQueryTradeResultBySerialField.BankBranchID));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqQueryTradeResultBySerialField.BrokerID));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqQueryTradeResultBySerialField.BrokerBranchID));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqQueryTradeResultBySerialField.TradeDate));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqQueryTradeResultBySerialField.TradeTime));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqQueryTradeResultBySerialField.BankSerial));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqQueryTradeResultBySerialField.TradingDay));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqQueryTradeResultBySerialField.PlateSerial));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqQueryTradeResultBySerialField.LastFragment));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqQueryTradeResultBySerialField.SessionID));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","流水号","TThostFtdcSerialType", "Reference", &(m_ThostFtdcReqQueryTradeResultBySerialField.Reference));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","本流水号发布者的机构类型","TThostFtdcInstitutionTypeType", "RefrenceIssureType", &(m_ThostFtdcReqQueryTradeResultBySerialField.RefrenceIssureType));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","本流水号发布者机构编码","TThostFtdcOrganCodeType", "RefrenceIssure", &(m_ThostFtdcReqQueryTradeResultBySerialField.RefrenceIssure));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcReqQueryTradeResultBySerialField.CustomerName));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcReqQueryTradeResultBySerialField.IdCardType));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcReqQueryTradeResultBySerialField.IdentifiedCardNo));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcReqQueryTradeResultBySerialField.CustType));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcReqQueryTradeResultBySerialField.BankAccount));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcReqQueryTradeResultBySerialField.BankPassWord));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcReqQueryTradeResultBySerialField.AccountID));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcReqQueryTradeResultBySerialField.Password));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcReqQueryTradeResultBySerialField.CurrencyID));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","转帐金额","TThostFtdcTradeAmountType", "TradeAmount", &(m_ThostFtdcReqQueryTradeResultBySerialField.TradeAmount));
	RegField("CThostFtdcReqQueryTradeResultBySerialField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqQueryTradeResultBySerialField.Digest));

	RegField("CThostFtdcRspQueryTradeResultBySerialField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcRspQueryTradeResultBySerialField.TradeCode));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcRspQueryTradeResultBySerialField.BankID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcRspQueryTradeResultBySerialField.BankBranchID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspQueryTradeResultBySerialField.BrokerID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcRspQueryTradeResultBySerialField.BrokerBranchID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcRspQueryTradeResultBySerialField.TradeDate));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcRspQueryTradeResultBySerialField.TradeTime));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcRspQueryTradeResultBySerialField.BankSerial));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcRspQueryTradeResultBySerialField.TradingDay));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcRspQueryTradeResultBySerialField.PlateSerial));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcRspQueryTradeResultBySerialField.LastFragment));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspQueryTradeResultBySerialField.SessionID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcRspQueryTradeResultBySerialField.ErrorID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcRspQueryTradeResultBySerialField.ErrorMsg));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","流水号","TThostFtdcSerialType", "Reference", &(m_ThostFtdcRspQueryTradeResultBySerialField.Reference));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","本流水号发布者的机构类型","TThostFtdcInstitutionTypeType", "RefrenceIssureType", &(m_ThostFtdcRspQueryTradeResultBySerialField.RefrenceIssureType));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","本流水号发布者机构编码","TThostFtdcOrganCodeType", "RefrenceIssure", &(m_ThostFtdcRspQueryTradeResultBySerialField.RefrenceIssure));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","原始返回代码","TThostFtdcReturnCodeType", "OriginReturnCode", &(m_ThostFtdcRspQueryTradeResultBySerialField.OriginReturnCode));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","原始返回码描述","TThostFtdcDescrInfoForReturnCodeType", "OriginDescrInfoForReturnCode", &(m_ThostFtdcRspQueryTradeResultBySerialField.OriginDescrInfoForReturnCode));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcRspQueryTradeResultBySerialField.BankAccount));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcRspQueryTradeResultBySerialField.BankPassWord));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcRspQueryTradeResultBySerialField.AccountID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcRspQueryTradeResultBySerialField.Password));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcRspQueryTradeResultBySerialField.CurrencyID));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","转帐金额","TThostFtdcTradeAmountType", "TradeAmount", &(m_ThostFtdcRspQueryTradeResultBySerialField.TradeAmount));
	RegField("CThostFtdcRspQueryTradeResultBySerialField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcRspQueryTradeResultBySerialField.Digest));

	RegField("CThostFtdcReqDayEndFileReadyField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqDayEndFileReadyField.TradeCode));
	RegField("CThostFtdcReqDayEndFileReadyField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqDayEndFileReadyField.BankID));
	RegField("CThostFtdcReqDayEndFileReadyField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqDayEndFileReadyField.BankBranchID));
	RegField("CThostFtdcReqDayEndFileReadyField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqDayEndFileReadyField.BrokerID));
	RegField("CThostFtdcReqDayEndFileReadyField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqDayEndFileReadyField.BrokerBranchID));
	RegField("CThostFtdcReqDayEndFileReadyField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqDayEndFileReadyField.TradeDate));
	RegField("CThostFtdcReqDayEndFileReadyField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqDayEndFileReadyField.TradeTime));
	RegField("CThostFtdcReqDayEndFileReadyField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqDayEndFileReadyField.BankSerial));
	RegField("CThostFtdcReqDayEndFileReadyField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqDayEndFileReadyField.TradingDay));
	RegField("CThostFtdcReqDayEndFileReadyField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqDayEndFileReadyField.PlateSerial));
	RegField("CThostFtdcReqDayEndFileReadyField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqDayEndFileReadyField.LastFragment));
	RegField("CThostFtdcReqDayEndFileReadyField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqDayEndFileReadyField.SessionID));
	RegField("CThostFtdcReqDayEndFileReadyField","文件业务功能","TThostFtdcFileBusinessCodeType", "FileBusinessCode", &(m_ThostFtdcReqDayEndFileReadyField.FileBusinessCode));
	RegField("CThostFtdcReqDayEndFileReadyField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcReqDayEndFileReadyField.Digest));

	RegField("CThostFtdcReturnResultField","返回代码","TThostFtdcReturnCodeType", "ReturnCode", &(m_ThostFtdcReturnResultField.ReturnCode));
	RegField("CThostFtdcReturnResultField","返回码描述","TThostFtdcDescrInfoForReturnCodeType", "DescrInfoForReturnCode", &(m_ThostFtdcReturnResultField.DescrInfoForReturnCode));

	RegField("CThostFtdcVerifyFuturePasswordField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcVerifyFuturePasswordField.TradeCode));
	RegField("CThostFtdcVerifyFuturePasswordField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcVerifyFuturePasswordField.BankID));
	RegField("CThostFtdcVerifyFuturePasswordField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcVerifyFuturePasswordField.BankBranchID));
	RegField("CThostFtdcVerifyFuturePasswordField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcVerifyFuturePasswordField.BrokerID));
	RegField("CThostFtdcVerifyFuturePasswordField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcVerifyFuturePasswordField.BrokerBranchID));
	RegField("CThostFtdcVerifyFuturePasswordField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcVerifyFuturePasswordField.TradeDate));
	RegField("CThostFtdcVerifyFuturePasswordField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcVerifyFuturePasswordField.TradeTime));
	RegField("CThostFtdcVerifyFuturePasswordField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcVerifyFuturePasswordField.BankSerial));
	RegField("CThostFtdcVerifyFuturePasswordField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcVerifyFuturePasswordField.TradingDay));
	RegField("CThostFtdcVerifyFuturePasswordField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcVerifyFuturePasswordField.PlateSerial));
	RegField("CThostFtdcVerifyFuturePasswordField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcVerifyFuturePasswordField.LastFragment));
	RegField("CThostFtdcVerifyFuturePasswordField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcVerifyFuturePasswordField.SessionID));
	RegField("CThostFtdcVerifyFuturePasswordField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcVerifyFuturePasswordField.AccountID));
	RegField("CThostFtdcVerifyFuturePasswordField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcVerifyFuturePasswordField.Password));
	RegField("CThostFtdcVerifyFuturePasswordField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcVerifyFuturePasswordField.BankAccount));
	RegField("CThostFtdcVerifyFuturePasswordField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcVerifyFuturePasswordField.BankPassWord));
	RegField("CThostFtdcVerifyFuturePasswordField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcVerifyFuturePasswordField.InstallID));
	RegField("CThostFtdcVerifyFuturePasswordField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcVerifyFuturePasswordField.TID));
	RegField("CThostFtdcVerifyFuturePasswordField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcVerifyFuturePasswordField.CurrencyID));

	RegField("CThostFtdcVerifyCustInfoField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcVerifyCustInfoField.CustomerName));
	RegField("CThostFtdcVerifyCustInfoField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcVerifyCustInfoField.IdCardType));
	RegField("CThostFtdcVerifyCustInfoField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcVerifyCustInfoField.IdentifiedCardNo));
	RegField("CThostFtdcVerifyCustInfoField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcVerifyCustInfoField.CustType));

	RegField("CThostFtdcVerifyFuturePasswordAndCustInfoField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcVerifyFuturePasswordAndCustInfoField.CustomerName));
	RegField("CThostFtdcVerifyFuturePasswordAndCustInfoField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcVerifyFuturePasswordAndCustInfoField.IdCardType));
	RegField("CThostFtdcVerifyFuturePasswordAndCustInfoField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcVerifyFuturePasswordAndCustInfoField.IdentifiedCardNo));
	RegField("CThostFtdcVerifyFuturePasswordAndCustInfoField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcVerifyFuturePasswordAndCustInfoField.CustType));
	RegField("CThostFtdcVerifyFuturePasswordAndCustInfoField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcVerifyFuturePasswordAndCustInfoField.AccountID));
	RegField("CThostFtdcVerifyFuturePasswordAndCustInfoField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcVerifyFuturePasswordAndCustInfoField.Password));
	RegField("CThostFtdcVerifyFuturePasswordAndCustInfoField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcVerifyFuturePasswordAndCustInfoField.CurrencyID));

	RegField("CThostFtdcDepositResultInformField","出入金流水号，该流水号为银期报盘返回的流水号","TThostFtdcDepositSeqNoType", "DepositSeqNo", &(m_ThostFtdcDepositResultInformField.DepositSeqNo));
	RegField("CThostFtdcDepositResultInformField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcDepositResultInformField.BrokerID));
	RegField("CThostFtdcDepositResultInformField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcDepositResultInformField.InvestorID));
	RegField("CThostFtdcDepositResultInformField","入金金额","TThostFtdcMoneyType", "Deposit", &(m_ThostFtdcDepositResultInformField.Deposit));
	RegField("CThostFtdcDepositResultInformField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcDepositResultInformField.RequestID));
	RegField("CThostFtdcDepositResultInformField","返回代码","TThostFtdcReturnCodeType", "ReturnCode", &(m_ThostFtdcDepositResultInformField.ReturnCode));
	RegField("CThostFtdcDepositResultInformField","返回码描述","TThostFtdcDescrInfoForReturnCodeType", "DescrInfoForReturnCode", &(m_ThostFtdcDepositResultInformField.DescrInfoForReturnCode));

	RegField("CThostFtdcReqSyncKeyField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcReqSyncKeyField.TradeCode));
	RegField("CThostFtdcReqSyncKeyField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcReqSyncKeyField.BankID));
	RegField("CThostFtdcReqSyncKeyField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcReqSyncKeyField.BankBranchID));
	RegField("CThostFtdcReqSyncKeyField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcReqSyncKeyField.BrokerID));
	RegField("CThostFtdcReqSyncKeyField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcReqSyncKeyField.BrokerBranchID));
	RegField("CThostFtdcReqSyncKeyField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcReqSyncKeyField.TradeDate));
	RegField("CThostFtdcReqSyncKeyField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcReqSyncKeyField.TradeTime));
	RegField("CThostFtdcReqSyncKeyField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcReqSyncKeyField.BankSerial));
	RegField("CThostFtdcReqSyncKeyField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcReqSyncKeyField.TradingDay));
	RegField("CThostFtdcReqSyncKeyField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcReqSyncKeyField.PlateSerial));
	RegField("CThostFtdcReqSyncKeyField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcReqSyncKeyField.LastFragment));
	RegField("CThostFtdcReqSyncKeyField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcReqSyncKeyField.SessionID));
	RegField("CThostFtdcReqSyncKeyField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcReqSyncKeyField.InstallID));
	RegField("CThostFtdcReqSyncKeyField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcReqSyncKeyField.UserID));
	RegField("CThostFtdcReqSyncKeyField","交易核心给银期报盘的消息","TThostFtdcAddInfoType", "Message", &(m_ThostFtdcReqSyncKeyField.Message));
	RegField("CThostFtdcReqSyncKeyField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcReqSyncKeyField.DeviceID));
	RegField("CThostFtdcReqSyncKeyField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcReqSyncKeyField.BrokerIDByBank));
	RegField("CThostFtdcReqSyncKeyField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcReqSyncKeyField.OperNo));
	RegField("CThostFtdcReqSyncKeyField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcReqSyncKeyField.RequestID));
	RegField("CThostFtdcReqSyncKeyField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcReqSyncKeyField.TID));

	RegField("CThostFtdcRspSyncKeyField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcRspSyncKeyField.TradeCode));
	RegField("CThostFtdcRspSyncKeyField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcRspSyncKeyField.BankID));
	RegField("CThostFtdcRspSyncKeyField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcRspSyncKeyField.BankBranchID));
	RegField("CThostFtdcRspSyncKeyField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcRspSyncKeyField.BrokerID));
	RegField("CThostFtdcRspSyncKeyField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcRspSyncKeyField.BrokerBranchID));
	RegField("CThostFtdcRspSyncKeyField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcRspSyncKeyField.TradeDate));
	RegField("CThostFtdcRspSyncKeyField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcRspSyncKeyField.TradeTime));
	RegField("CThostFtdcRspSyncKeyField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcRspSyncKeyField.BankSerial));
	RegField("CThostFtdcRspSyncKeyField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcRspSyncKeyField.TradingDay));
	RegField("CThostFtdcRspSyncKeyField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcRspSyncKeyField.PlateSerial));
	RegField("CThostFtdcRspSyncKeyField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcRspSyncKeyField.LastFragment));
	RegField("CThostFtdcRspSyncKeyField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcRspSyncKeyField.SessionID));
	RegField("CThostFtdcRspSyncKeyField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcRspSyncKeyField.InstallID));
	RegField("CThostFtdcRspSyncKeyField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcRspSyncKeyField.UserID));
	RegField("CThostFtdcRspSyncKeyField","交易核心给银期报盘的消息","TThostFtdcAddInfoType", "Message", &(m_ThostFtdcRspSyncKeyField.Message));
	RegField("CThostFtdcRspSyncKeyField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcRspSyncKeyField.DeviceID));
	RegField("CThostFtdcRspSyncKeyField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcRspSyncKeyField.BrokerIDByBank));
	RegField("CThostFtdcRspSyncKeyField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcRspSyncKeyField.OperNo));
	RegField("CThostFtdcRspSyncKeyField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcRspSyncKeyField.RequestID));
	RegField("CThostFtdcRspSyncKeyField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcRspSyncKeyField.TID));
	RegField("CThostFtdcRspSyncKeyField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcRspSyncKeyField.ErrorID));
	RegField("CThostFtdcRspSyncKeyField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcRspSyncKeyField.ErrorMsg));

	RegField("CThostFtdcNotifyQueryAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcNotifyQueryAccountField.TradeCode));
	RegField("CThostFtdcNotifyQueryAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcNotifyQueryAccountField.BankID));
	RegField("CThostFtdcNotifyQueryAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcNotifyQueryAccountField.BankBranchID));
	RegField("CThostFtdcNotifyQueryAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcNotifyQueryAccountField.BrokerID));
	RegField("CThostFtdcNotifyQueryAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcNotifyQueryAccountField.BrokerBranchID));
	RegField("CThostFtdcNotifyQueryAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcNotifyQueryAccountField.TradeDate));
	RegField("CThostFtdcNotifyQueryAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcNotifyQueryAccountField.TradeTime));
	RegField("CThostFtdcNotifyQueryAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcNotifyQueryAccountField.BankSerial));
	RegField("CThostFtdcNotifyQueryAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcNotifyQueryAccountField.TradingDay));
	RegField("CThostFtdcNotifyQueryAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcNotifyQueryAccountField.PlateSerial));
	RegField("CThostFtdcNotifyQueryAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcNotifyQueryAccountField.LastFragment));
	RegField("CThostFtdcNotifyQueryAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcNotifyQueryAccountField.SessionID));
	RegField("CThostFtdcNotifyQueryAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcNotifyQueryAccountField.CustomerName));
	RegField("CThostFtdcNotifyQueryAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcNotifyQueryAccountField.IdCardType));
	RegField("CThostFtdcNotifyQueryAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcNotifyQueryAccountField.IdentifiedCardNo));
	RegField("CThostFtdcNotifyQueryAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcNotifyQueryAccountField.CustType));
	RegField("CThostFtdcNotifyQueryAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcNotifyQueryAccountField.BankAccount));
	RegField("CThostFtdcNotifyQueryAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcNotifyQueryAccountField.BankPassWord));
	RegField("CThostFtdcNotifyQueryAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcNotifyQueryAccountField.AccountID));
	RegField("CThostFtdcNotifyQueryAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcNotifyQueryAccountField.Password));
	RegField("CThostFtdcNotifyQueryAccountField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcNotifyQueryAccountField.FutureSerial));
	RegField("CThostFtdcNotifyQueryAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcNotifyQueryAccountField.InstallID));
	RegField("CThostFtdcNotifyQueryAccountField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcNotifyQueryAccountField.UserID));
	RegField("CThostFtdcNotifyQueryAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcNotifyQueryAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcNotifyQueryAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcNotifyQueryAccountField.CurrencyID));
	RegField("CThostFtdcNotifyQueryAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcNotifyQueryAccountField.Digest));
	RegField("CThostFtdcNotifyQueryAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcNotifyQueryAccountField.BankAccType));
	RegField("CThostFtdcNotifyQueryAccountField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcNotifyQueryAccountField.DeviceID));
	RegField("CThostFtdcNotifyQueryAccountField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcNotifyQueryAccountField.BankSecuAccType));
	RegField("CThostFtdcNotifyQueryAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcNotifyQueryAccountField.BrokerIDByBank));
	RegField("CThostFtdcNotifyQueryAccountField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcNotifyQueryAccountField.BankSecuAcc));
	RegField("CThostFtdcNotifyQueryAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcNotifyQueryAccountField.BankPwdFlag));
	RegField("CThostFtdcNotifyQueryAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcNotifyQueryAccountField.SecuPwdFlag));
	RegField("CThostFtdcNotifyQueryAccountField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcNotifyQueryAccountField.OperNo));
	RegField("CThostFtdcNotifyQueryAccountField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcNotifyQueryAccountField.RequestID));
	RegField("CThostFtdcNotifyQueryAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcNotifyQueryAccountField.TID));
	RegField("CThostFtdcNotifyQueryAccountField","银行可用金额","TThostFtdcTradeAmountType", "BankUseAmount", &(m_ThostFtdcNotifyQueryAccountField.BankUseAmount));
	RegField("CThostFtdcNotifyQueryAccountField","银行可取金额","TThostFtdcTradeAmountType", "BankFetchAmount", &(m_ThostFtdcNotifyQueryAccountField.BankFetchAmount));
	RegField("CThostFtdcNotifyQueryAccountField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcNotifyQueryAccountField.ErrorID));
	RegField("CThostFtdcNotifyQueryAccountField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcNotifyQueryAccountField.ErrorMsg));

	RegField("CThostFtdcTransferSerialField","平台流水号","TThostFtdcPlateSerialType", "PlateSerial", &(m_ThostFtdcTransferSerialField.PlateSerial));
	RegField("CThostFtdcTransferSerialField","交易发起方日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcTransferSerialField.TradeDate));
	RegField("CThostFtdcTransferSerialField","交易日期","TThostFtdcDateType", "TradingDay", &(m_ThostFtdcTransferSerialField.TradingDay));
	RegField("CThostFtdcTransferSerialField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcTransferSerialField.TradeTime));
	RegField("CThostFtdcTransferSerialField","交易代码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcTransferSerialField.TradeCode));
	RegField("CThostFtdcTransferSerialField","会话编号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcTransferSerialField.SessionID));
	RegField("CThostFtdcTransferSerialField","银行编码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcTransferSerialField.BankID));
	RegField("CThostFtdcTransferSerialField","银行分支机构编码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcTransferSerialField.BankBranchID));
	RegField("CThostFtdcTransferSerialField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcTransferSerialField.BankAccType));
	RegField("CThostFtdcTransferSerialField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcTransferSerialField.BankAccount));
	RegField("CThostFtdcTransferSerialField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcTransferSerialField.BankSerial));
	RegField("CThostFtdcTransferSerialField","期货公司编码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTransferSerialField.BrokerID));
	RegField("CThostFtdcTransferSerialField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcTransferSerialField.BrokerBranchID));
	RegField("CThostFtdcTransferSerialField","期货公司帐号类型","TThostFtdcFutureAccTypeType", "FutureAccType", &(m_ThostFtdcTransferSerialField.FutureAccType));
	RegField("CThostFtdcTransferSerialField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcTransferSerialField.AccountID));
	RegField("CThostFtdcTransferSerialField","投资者代码","TThostFtdcInvestorIDType", "InvestorID", &(m_ThostFtdcTransferSerialField.InvestorID));
	RegField("CThostFtdcTransferSerialField","期货公司流水号","TThostFtdcFutureSerialType", "FutureSerial", &(m_ThostFtdcTransferSerialField.FutureSerial));
	RegField("CThostFtdcTransferSerialField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcTransferSerialField.IdCardType));
	RegField("CThostFtdcTransferSerialField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcTransferSerialField.IdentifiedCardNo));
	RegField("CThostFtdcTransferSerialField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcTransferSerialField.CurrencyID));
	RegField("CThostFtdcTransferSerialField","交易金额","TThostFtdcTradeAmountType", "TradeAmount", &(m_ThostFtdcTransferSerialField.TradeAmount));
	RegField("CThostFtdcTransferSerialField","应收客户费用","TThostFtdcCustFeeType", "CustFee", &(m_ThostFtdcTransferSerialField.CustFee));
	RegField("CThostFtdcTransferSerialField","应收期货公司费用","TThostFtdcFutureFeeType", "BrokerFee", &(m_ThostFtdcTransferSerialField.BrokerFee));
	RegField("CThostFtdcTransferSerialField","有效标志","TThostFtdcAvailabilityFlagType", "AvailabilityFlag", &(m_ThostFtdcTransferSerialField.AvailabilityFlag));
	RegField("CThostFtdcTransferSerialField","操作员","TThostFtdcOperatorCodeType", "OperatorCode", &(m_ThostFtdcTransferSerialField.OperatorCode));
	RegField("CThostFtdcTransferSerialField","新银行帐号","TThostFtdcBankAccountType", "BankNewAccount", &(m_ThostFtdcTransferSerialField.BankNewAccount));
	RegField("CThostFtdcTransferSerialField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcTransferSerialField.ErrorID));
	RegField("CThostFtdcTransferSerialField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcTransferSerialField.ErrorMsg));

	RegField("CThostFtdcQryTransferSerialField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryTransferSerialField.BrokerID));
	RegField("CThostFtdcQryTransferSerialField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcQryTransferSerialField.AccountID));
	RegField("CThostFtdcQryTransferSerialField","银行编码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcQryTransferSerialField.BankID));
	RegField("CThostFtdcQryTransferSerialField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcQryTransferSerialField.CurrencyID));

	RegField("CThostFtdcNotifyFutureSignInField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcNotifyFutureSignInField.TradeCode));
	RegField("CThostFtdcNotifyFutureSignInField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcNotifyFutureSignInField.BankID));
	RegField("CThostFtdcNotifyFutureSignInField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcNotifyFutureSignInField.BankBranchID));
	RegField("CThostFtdcNotifyFutureSignInField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcNotifyFutureSignInField.BrokerID));
	RegField("CThostFtdcNotifyFutureSignInField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcNotifyFutureSignInField.BrokerBranchID));
	RegField("CThostFtdcNotifyFutureSignInField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcNotifyFutureSignInField.TradeDate));
	RegField("CThostFtdcNotifyFutureSignInField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcNotifyFutureSignInField.TradeTime));
	RegField("CThostFtdcNotifyFutureSignInField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcNotifyFutureSignInField.BankSerial));
	RegField("CThostFtdcNotifyFutureSignInField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcNotifyFutureSignInField.TradingDay));
	RegField("CThostFtdcNotifyFutureSignInField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcNotifyFutureSignInField.PlateSerial));
	RegField("CThostFtdcNotifyFutureSignInField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcNotifyFutureSignInField.LastFragment));
	RegField("CThostFtdcNotifyFutureSignInField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcNotifyFutureSignInField.SessionID));
	RegField("CThostFtdcNotifyFutureSignInField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcNotifyFutureSignInField.InstallID));
	RegField("CThostFtdcNotifyFutureSignInField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcNotifyFutureSignInField.UserID));
	RegField("CThostFtdcNotifyFutureSignInField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcNotifyFutureSignInField.Digest));
	RegField("CThostFtdcNotifyFutureSignInField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcNotifyFutureSignInField.CurrencyID));
	RegField("CThostFtdcNotifyFutureSignInField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcNotifyFutureSignInField.DeviceID));
	RegField("CThostFtdcNotifyFutureSignInField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcNotifyFutureSignInField.BrokerIDByBank));
	RegField("CThostFtdcNotifyFutureSignInField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcNotifyFutureSignInField.OperNo));
	RegField("CThostFtdcNotifyFutureSignInField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcNotifyFutureSignInField.RequestID));
	RegField("CThostFtdcNotifyFutureSignInField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcNotifyFutureSignInField.TID));
	RegField("CThostFtdcNotifyFutureSignInField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcNotifyFutureSignInField.ErrorID));
	RegField("CThostFtdcNotifyFutureSignInField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcNotifyFutureSignInField.ErrorMsg));
	RegField("CThostFtdcNotifyFutureSignInField","PIN密钥","TThostFtdcPasswordKeyType", "PinKey", &(m_ThostFtdcNotifyFutureSignInField.PinKey));
	RegField("CThostFtdcNotifyFutureSignInField","MAC密钥","TThostFtdcPasswordKeyType", "MacKey", &(m_ThostFtdcNotifyFutureSignInField.MacKey));

	RegField("CThostFtdcNotifyFutureSignOutField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcNotifyFutureSignOutField.TradeCode));
	RegField("CThostFtdcNotifyFutureSignOutField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcNotifyFutureSignOutField.BankID));
	RegField("CThostFtdcNotifyFutureSignOutField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcNotifyFutureSignOutField.BankBranchID));
	RegField("CThostFtdcNotifyFutureSignOutField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcNotifyFutureSignOutField.BrokerID));
	RegField("CThostFtdcNotifyFutureSignOutField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcNotifyFutureSignOutField.BrokerBranchID));
	RegField("CThostFtdcNotifyFutureSignOutField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcNotifyFutureSignOutField.TradeDate));
	RegField("CThostFtdcNotifyFutureSignOutField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcNotifyFutureSignOutField.TradeTime));
	RegField("CThostFtdcNotifyFutureSignOutField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcNotifyFutureSignOutField.BankSerial));
	RegField("CThostFtdcNotifyFutureSignOutField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcNotifyFutureSignOutField.TradingDay));
	RegField("CThostFtdcNotifyFutureSignOutField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcNotifyFutureSignOutField.PlateSerial));
	RegField("CThostFtdcNotifyFutureSignOutField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcNotifyFutureSignOutField.LastFragment));
	RegField("CThostFtdcNotifyFutureSignOutField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcNotifyFutureSignOutField.SessionID));
	RegField("CThostFtdcNotifyFutureSignOutField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcNotifyFutureSignOutField.InstallID));
	RegField("CThostFtdcNotifyFutureSignOutField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcNotifyFutureSignOutField.UserID));
	RegField("CThostFtdcNotifyFutureSignOutField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcNotifyFutureSignOutField.Digest));
	RegField("CThostFtdcNotifyFutureSignOutField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcNotifyFutureSignOutField.CurrencyID));
	RegField("CThostFtdcNotifyFutureSignOutField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcNotifyFutureSignOutField.DeviceID));
	RegField("CThostFtdcNotifyFutureSignOutField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcNotifyFutureSignOutField.BrokerIDByBank));
	RegField("CThostFtdcNotifyFutureSignOutField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcNotifyFutureSignOutField.OperNo));
	RegField("CThostFtdcNotifyFutureSignOutField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcNotifyFutureSignOutField.RequestID));
	RegField("CThostFtdcNotifyFutureSignOutField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcNotifyFutureSignOutField.TID));
	RegField("CThostFtdcNotifyFutureSignOutField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcNotifyFutureSignOutField.ErrorID));
	RegField("CThostFtdcNotifyFutureSignOutField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcNotifyFutureSignOutField.ErrorMsg));

	RegField("CThostFtdcNotifySyncKeyField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcNotifySyncKeyField.TradeCode));
	RegField("CThostFtdcNotifySyncKeyField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcNotifySyncKeyField.BankID));
	RegField("CThostFtdcNotifySyncKeyField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcNotifySyncKeyField.BankBranchID));
	RegField("CThostFtdcNotifySyncKeyField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcNotifySyncKeyField.BrokerID));
	RegField("CThostFtdcNotifySyncKeyField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcNotifySyncKeyField.BrokerBranchID));
	RegField("CThostFtdcNotifySyncKeyField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcNotifySyncKeyField.TradeDate));
	RegField("CThostFtdcNotifySyncKeyField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcNotifySyncKeyField.TradeTime));
	RegField("CThostFtdcNotifySyncKeyField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcNotifySyncKeyField.BankSerial));
	RegField("CThostFtdcNotifySyncKeyField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcNotifySyncKeyField.TradingDay));
	RegField("CThostFtdcNotifySyncKeyField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcNotifySyncKeyField.PlateSerial));
	RegField("CThostFtdcNotifySyncKeyField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcNotifySyncKeyField.LastFragment));
	RegField("CThostFtdcNotifySyncKeyField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcNotifySyncKeyField.SessionID));
	RegField("CThostFtdcNotifySyncKeyField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcNotifySyncKeyField.InstallID));
	RegField("CThostFtdcNotifySyncKeyField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcNotifySyncKeyField.UserID));
	RegField("CThostFtdcNotifySyncKeyField","交易核心给银期报盘的消息","TThostFtdcAddInfoType", "Message", &(m_ThostFtdcNotifySyncKeyField.Message));
	RegField("CThostFtdcNotifySyncKeyField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcNotifySyncKeyField.DeviceID));
	RegField("CThostFtdcNotifySyncKeyField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcNotifySyncKeyField.BrokerIDByBank));
	RegField("CThostFtdcNotifySyncKeyField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcNotifySyncKeyField.OperNo));
	RegField("CThostFtdcNotifySyncKeyField","请求编号","TThostFtdcRequestIDType", "RequestID", &(m_ThostFtdcNotifySyncKeyField.RequestID));
	RegField("CThostFtdcNotifySyncKeyField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcNotifySyncKeyField.TID));
	RegField("CThostFtdcNotifySyncKeyField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcNotifySyncKeyField.ErrorID));
	RegField("CThostFtdcNotifySyncKeyField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcNotifySyncKeyField.ErrorMsg));

	RegField("CThostFtdcQryAccountregisterField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryAccountregisterField.BrokerID));
	RegField("CThostFtdcQryAccountregisterField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcQryAccountregisterField.AccountID));
	RegField("CThostFtdcQryAccountregisterField","银行编码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcQryAccountregisterField.BankID));
	RegField("CThostFtdcQryAccountregisterField","银行分支机构编码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcQryAccountregisterField.BankBranchID));
	RegField("CThostFtdcQryAccountregisterField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcQryAccountregisterField.CurrencyID));

	RegField("CThostFtdcAccountregisterField","交易日期","TThostFtdcTradeDateType", "TradeDay", &(m_ThostFtdcAccountregisterField.TradeDay));
	RegField("CThostFtdcAccountregisterField","银行编码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcAccountregisterField.BankID));
	RegField("CThostFtdcAccountregisterField","银行分支机构编码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcAccountregisterField.BankBranchID));
	RegField("CThostFtdcAccountregisterField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcAccountregisterField.BankAccount));
	RegField("CThostFtdcAccountregisterField","期货公司编码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcAccountregisterField.BrokerID));
	RegField("CThostFtdcAccountregisterField","期货公司分支机构编码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcAccountregisterField.BrokerBranchID));
	RegField("CThostFtdcAccountregisterField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcAccountregisterField.AccountID));
	RegField("CThostFtdcAccountregisterField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcAccountregisterField.IdCardType));
	RegField("CThostFtdcAccountregisterField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcAccountregisterField.IdentifiedCardNo));
	RegField("CThostFtdcAccountregisterField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcAccountregisterField.CustomerName));
	RegField("CThostFtdcAccountregisterField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcAccountregisterField.CurrencyID));
	RegField("CThostFtdcAccountregisterField","开销户类别","TThostFtdcOpenOrDestroyType", "OpenOrDestroy", &(m_ThostFtdcAccountregisterField.OpenOrDestroy));
	RegField("CThostFtdcAccountregisterField","签约日期","TThostFtdcTradeDateType", "RegDate", &(m_ThostFtdcAccountregisterField.RegDate));
	RegField("CThostFtdcAccountregisterField","解约日期","TThostFtdcTradeDateType", "OutDate", &(m_ThostFtdcAccountregisterField.OutDate));
	RegField("CThostFtdcAccountregisterField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcAccountregisterField.TID));
	RegField("CThostFtdcAccountregisterField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcAccountregisterField.CustType));
	RegField("CThostFtdcAccountregisterField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcAccountregisterField.BankAccType));

	RegField("CThostFtdcOpenAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcOpenAccountField.TradeCode));
	RegField("CThostFtdcOpenAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcOpenAccountField.BankID));
	RegField("CThostFtdcOpenAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcOpenAccountField.BankBranchID));
	RegField("CThostFtdcOpenAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcOpenAccountField.BrokerID));
	RegField("CThostFtdcOpenAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcOpenAccountField.BrokerBranchID));
	RegField("CThostFtdcOpenAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcOpenAccountField.TradeDate));
	RegField("CThostFtdcOpenAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcOpenAccountField.TradeTime));
	RegField("CThostFtdcOpenAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcOpenAccountField.BankSerial));
	RegField("CThostFtdcOpenAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcOpenAccountField.TradingDay));
	RegField("CThostFtdcOpenAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcOpenAccountField.PlateSerial));
	RegField("CThostFtdcOpenAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcOpenAccountField.LastFragment));
	RegField("CThostFtdcOpenAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcOpenAccountField.SessionID));
	RegField("CThostFtdcOpenAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcOpenAccountField.CustomerName));
	RegField("CThostFtdcOpenAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcOpenAccountField.IdCardType));
	RegField("CThostFtdcOpenAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcOpenAccountField.IdentifiedCardNo));
	RegField("CThostFtdcOpenAccountField","性别","TThostFtdcGenderType", "Gender", &(m_ThostFtdcOpenAccountField.Gender));
	RegField("CThostFtdcOpenAccountField","国家代码","TThostFtdcCountryCodeType", "CountryCode", &(m_ThostFtdcOpenAccountField.CountryCode));
	RegField("CThostFtdcOpenAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcOpenAccountField.CustType));
	RegField("CThostFtdcOpenAccountField","地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcOpenAccountField.Address));
	RegField("CThostFtdcOpenAccountField","邮编","TThostFtdcZipCodeType", "ZipCode", &(m_ThostFtdcOpenAccountField.ZipCode));
	RegField("CThostFtdcOpenAccountField","电话号码","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcOpenAccountField.Telephone));
	RegField("CThostFtdcOpenAccountField","手机","TThostFtdcMobilePhoneType", "MobilePhone", &(m_ThostFtdcOpenAccountField.MobilePhone));
	RegField("CThostFtdcOpenAccountField","传真","TThostFtdcFaxType", "Fax", &(m_ThostFtdcOpenAccountField.Fax));
	RegField("CThostFtdcOpenAccountField","电子邮件","TThostFtdcEMailType", "EMail", &(m_ThostFtdcOpenAccountField.EMail));
	RegField("CThostFtdcOpenAccountField","资金账户状态","TThostFtdcMoneyAccountStatusType", "MoneyAccountStatus", &(m_ThostFtdcOpenAccountField.MoneyAccountStatus));
	RegField("CThostFtdcOpenAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcOpenAccountField.BankAccount));
	RegField("CThostFtdcOpenAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcOpenAccountField.BankPassWord));
	RegField("CThostFtdcOpenAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcOpenAccountField.AccountID));
	RegField("CThostFtdcOpenAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcOpenAccountField.Password));
	RegField("CThostFtdcOpenAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcOpenAccountField.InstallID));
	RegField("CThostFtdcOpenAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcOpenAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcOpenAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcOpenAccountField.CurrencyID));
	RegField("CThostFtdcOpenAccountField","汇钞标志","TThostFtdcCashExchangeCodeType", "CashExchangeCode", &(m_ThostFtdcOpenAccountField.CashExchangeCode));
	RegField("CThostFtdcOpenAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcOpenAccountField.Digest));
	RegField("CThostFtdcOpenAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcOpenAccountField.BankAccType));
	RegField("CThostFtdcOpenAccountField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcOpenAccountField.DeviceID));
	RegField("CThostFtdcOpenAccountField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcOpenAccountField.BankSecuAccType));
	RegField("CThostFtdcOpenAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcOpenAccountField.BrokerIDByBank));
	RegField("CThostFtdcOpenAccountField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcOpenAccountField.BankSecuAcc));
	RegField("CThostFtdcOpenAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcOpenAccountField.BankPwdFlag));
	RegField("CThostFtdcOpenAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcOpenAccountField.SecuPwdFlag));
	RegField("CThostFtdcOpenAccountField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcOpenAccountField.OperNo));
	RegField("CThostFtdcOpenAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcOpenAccountField.TID));
	RegField("CThostFtdcOpenAccountField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcOpenAccountField.UserID));
	RegField("CThostFtdcOpenAccountField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcOpenAccountField.ErrorID));
	RegField("CThostFtdcOpenAccountField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcOpenAccountField.ErrorMsg));

	RegField("CThostFtdcCancelAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcCancelAccountField.TradeCode));
	RegField("CThostFtdcCancelAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcCancelAccountField.BankID));
	RegField("CThostFtdcCancelAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcCancelAccountField.BankBranchID));
	RegField("CThostFtdcCancelAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcCancelAccountField.BrokerID));
	RegField("CThostFtdcCancelAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcCancelAccountField.BrokerBranchID));
	RegField("CThostFtdcCancelAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcCancelAccountField.TradeDate));
	RegField("CThostFtdcCancelAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcCancelAccountField.TradeTime));
	RegField("CThostFtdcCancelAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcCancelAccountField.BankSerial));
	RegField("CThostFtdcCancelAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcCancelAccountField.TradingDay));
	RegField("CThostFtdcCancelAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcCancelAccountField.PlateSerial));
	RegField("CThostFtdcCancelAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcCancelAccountField.LastFragment));
	RegField("CThostFtdcCancelAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcCancelAccountField.SessionID));
	RegField("CThostFtdcCancelAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcCancelAccountField.CustomerName));
	RegField("CThostFtdcCancelAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcCancelAccountField.IdCardType));
	RegField("CThostFtdcCancelAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcCancelAccountField.IdentifiedCardNo));
	RegField("CThostFtdcCancelAccountField","性别","TThostFtdcGenderType", "Gender", &(m_ThostFtdcCancelAccountField.Gender));
	RegField("CThostFtdcCancelAccountField","国家代码","TThostFtdcCountryCodeType", "CountryCode", &(m_ThostFtdcCancelAccountField.CountryCode));
	RegField("CThostFtdcCancelAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcCancelAccountField.CustType));
	RegField("CThostFtdcCancelAccountField","地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcCancelAccountField.Address));
	RegField("CThostFtdcCancelAccountField","邮编","TThostFtdcZipCodeType", "ZipCode", &(m_ThostFtdcCancelAccountField.ZipCode));
	RegField("CThostFtdcCancelAccountField","电话号码","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcCancelAccountField.Telephone));
	RegField("CThostFtdcCancelAccountField","手机","TThostFtdcMobilePhoneType", "MobilePhone", &(m_ThostFtdcCancelAccountField.MobilePhone));
	RegField("CThostFtdcCancelAccountField","传真","TThostFtdcFaxType", "Fax", &(m_ThostFtdcCancelAccountField.Fax));
	RegField("CThostFtdcCancelAccountField","电子邮件","TThostFtdcEMailType", "EMail", &(m_ThostFtdcCancelAccountField.EMail));
	RegField("CThostFtdcCancelAccountField","资金账户状态","TThostFtdcMoneyAccountStatusType", "MoneyAccountStatus", &(m_ThostFtdcCancelAccountField.MoneyAccountStatus));
	RegField("CThostFtdcCancelAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcCancelAccountField.BankAccount));
	RegField("CThostFtdcCancelAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcCancelAccountField.BankPassWord));
	RegField("CThostFtdcCancelAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcCancelAccountField.AccountID));
	RegField("CThostFtdcCancelAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcCancelAccountField.Password));
	RegField("CThostFtdcCancelAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcCancelAccountField.InstallID));
	RegField("CThostFtdcCancelAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcCancelAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcCancelAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcCancelAccountField.CurrencyID));
	RegField("CThostFtdcCancelAccountField","汇钞标志","TThostFtdcCashExchangeCodeType", "CashExchangeCode", &(m_ThostFtdcCancelAccountField.CashExchangeCode));
	RegField("CThostFtdcCancelAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcCancelAccountField.Digest));
	RegField("CThostFtdcCancelAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcCancelAccountField.BankAccType));
	RegField("CThostFtdcCancelAccountField","渠道标志","TThostFtdcDeviceIDType", "DeviceID", &(m_ThostFtdcCancelAccountField.DeviceID));
	RegField("CThostFtdcCancelAccountField","期货单位帐号类型","TThostFtdcBankAccTypeType", "BankSecuAccType", &(m_ThostFtdcCancelAccountField.BankSecuAccType));
	RegField("CThostFtdcCancelAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcCancelAccountField.BrokerIDByBank));
	RegField("CThostFtdcCancelAccountField","期货单位帐号","TThostFtdcBankAccountType", "BankSecuAcc", &(m_ThostFtdcCancelAccountField.BankSecuAcc));
	RegField("CThostFtdcCancelAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcCancelAccountField.BankPwdFlag));
	RegField("CThostFtdcCancelAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcCancelAccountField.SecuPwdFlag));
	RegField("CThostFtdcCancelAccountField","交易柜员","TThostFtdcOperNoType", "OperNo", &(m_ThostFtdcCancelAccountField.OperNo));
	RegField("CThostFtdcCancelAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcCancelAccountField.TID));
	RegField("CThostFtdcCancelAccountField","用户标识","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcCancelAccountField.UserID));
	RegField("CThostFtdcCancelAccountField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcCancelAccountField.ErrorID));
	RegField("CThostFtdcCancelAccountField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcCancelAccountField.ErrorMsg));

	RegField("CThostFtdcChangeAccountField","业务功能码","TThostFtdcTradeCodeType", "TradeCode", &(m_ThostFtdcChangeAccountField.TradeCode));
	RegField("CThostFtdcChangeAccountField","银行代码","TThostFtdcBankIDType", "BankID", &(m_ThostFtdcChangeAccountField.BankID));
	RegField("CThostFtdcChangeAccountField","银行分支机构代码","TThostFtdcBankBrchIDType", "BankBranchID", &(m_ThostFtdcChangeAccountField.BankBranchID));
	RegField("CThostFtdcChangeAccountField","期商代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcChangeAccountField.BrokerID));
	RegField("CThostFtdcChangeAccountField","期商分支机构代码","TThostFtdcFutureBranchIDType", "BrokerBranchID", &(m_ThostFtdcChangeAccountField.BrokerBranchID));
	RegField("CThostFtdcChangeAccountField","交易日期","TThostFtdcTradeDateType", "TradeDate", &(m_ThostFtdcChangeAccountField.TradeDate));
	RegField("CThostFtdcChangeAccountField","交易时间","TThostFtdcTradeTimeType", "TradeTime", &(m_ThostFtdcChangeAccountField.TradeTime));
	RegField("CThostFtdcChangeAccountField","银行流水号","TThostFtdcBankSerialType", "BankSerial", &(m_ThostFtdcChangeAccountField.BankSerial));
	RegField("CThostFtdcChangeAccountField","交易系统日期 ","TThostFtdcTradeDateType", "TradingDay", &(m_ThostFtdcChangeAccountField.TradingDay));
	RegField("CThostFtdcChangeAccountField","银期平台消息流水号","TThostFtdcSerialType", "PlateSerial", &(m_ThostFtdcChangeAccountField.PlateSerial));
	RegField("CThostFtdcChangeAccountField","最后分片标志","TThostFtdcLastFragmentType", "LastFragment", &(m_ThostFtdcChangeAccountField.LastFragment));
	RegField("CThostFtdcChangeAccountField","会话号","TThostFtdcSessionIDType", "SessionID", &(m_ThostFtdcChangeAccountField.SessionID));
	RegField("CThostFtdcChangeAccountField","客户姓名","TThostFtdcIndividualNameType", "CustomerName", &(m_ThostFtdcChangeAccountField.CustomerName));
	RegField("CThostFtdcChangeAccountField","证件类型","TThostFtdcIdCardTypeType", "IdCardType", &(m_ThostFtdcChangeAccountField.IdCardType));
	RegField("CThostFtdcChangeAccountField","证件号码","TThostFtdcIdentifiedCardNoType", "IdentifiedCardNo", &(m_ThostFtdcChangeAccountField.IdentifiedCardNo));
	RegField("CThostFtdcChangeAccountField","性别","TThostFtdcGenderType", "Gender", &(m_ThostFtdcChangeAccountField.Gender));
	RegField("CThostFtdcChangeAccountField","国家代码","TThostFtdcCountryCodeType", "CountryCode", &(m_ThostFtdcChangeAccountField.CountryCode));
	RegField("CThostFtdcChangeAccountField","客户类型","TThostFtdcCustTypeType", "CustType", &(m_ThostFtdcChangeAccountField.CustType));
	RegField("CThostFtdcChangeAccountField","地址","TThostFtdcAddressType", "Address", &(m_ThostFtdcChangeAccountField.Address));
	RegField("CThostFtdcChangeAccountField","邮编","TThostFtdcZipCodeType", "ZipCode", &(m_ThostFtdcChangeAccountField.ZipCode));
	RegField("CThostFtdcChangeAccountField","电话号码","TThostFtdcTelephoneType", "Telephone", &(m_ThostFtdcChangeAccountField.Telephone));
	RegField("CThostFtdcChangeAccountField","手机","TThostFtdcMobilePhoneType", "MobilePhone", &(m_ThostFtdcChangeAccountField.MobilePhone));
	RegField("CThostFtdcChangeAccountField","传真","TThostFtdcFaxType", "Fax", &(m_ThostFtdcChangeAccountField.Fax));
	RegField("CThostFtdcChangeAccountField","电子邮件","TThostFtdcEMailType", "EMail", &(m_ThostFtdcChangeAccountField.EMail));
	RegField("CThostFtdcChangeAccountField","资金账户状态","TThostFtdcMoneyAccountStatusType", "MoneyAccountStatus", &(m_ThostFtdcChangeAccountField.MoneyAccountStatus));
	RegField("CThostFtdcChangeAccountField","银行帐号","TThostFtdcBankAccountType", "BankAccount", &(m_ThostFtdcChangeAccountField.BankAccount));
	RegField("CThostFtdcChangeAccountField","银行密码","TThostFtdcPasswordType", "BankPassWord", &(m_ThostFtdcChangeAccountField.BankPassWord));
	RegField("CThostFtdcChangeAccountField","新银行帐号","TThostFtdcBankAccountType", "NewBankAccount", &(m_ThostFtdcChangeAccountField.NewBankAccount));
	RegField("CThostFtdcChangeAccountField","新银行密码","TThostFtdcPasswordType", "NewBankPassWord", &(m_ThostFtdcChangeAccountField.NewBankPassWord));
	RegField("CThostFtdcChangeAccountField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcChangeAccountField.AccountID));
	RegField("CThostFtdcChangeAccountField","期货密码","TThostFtdcPasswordType", "Password", &(m_ThostFtdcChangeAccountField.Password));
	RegField("CThostFtdcChangeAccountField","银行帐号类型","TThostFtdcBankAccTypeType", "BankAccType", &(m_ThostFtdcChangeAccountField.BankAccType));
	RegField("CThostFtdcChangeAccountField","安装编号","TThostFtdcInstallIDType", "InstallID", &(m_ThostFtdcChangeAccountField.InstallID));
	RegField("CThostFtdcChangeAccountField","验证客户证件号码标志","TThostFtdcYesNoIndicatorType", "VerifyCertNoFlag", &(m_ThostFtdcChangeAccountField.VerifyCertNoFlag));
	RegField("CThostFtdcChangeAccountField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcChangeAccountField.CurrencyID));
	RegField("CThostFtdcChangeAccountField","期货公司银行编码","TThostFtdcBankCodingForFutureType", "BrokerIDByBank", &(m_ThostFtdcChangeAccountField.BrokerIDByBank));
	RegField("CThostFtdcChangeAccountField","银行密码标志","TThostFtdcPwdFlagType", "BankPwdFlag", &(m_ThostFtdcChangeAccountField.BankPwdFlag));
	RegField("CThostFtdcChangeAccountField","期货资金密码核对标志","TThostFtdcPwdFlagType", "SecuPwdFlag", &(m_ThostFtdcChangeAccountField.SecuPwdFlag));
	RegField("CThostFtdcChangeAccountField","交易ID","TThostFtdcTIDType", "TID", &(m_ThostFtdcChangeAccountField.TID));
	RegField("CThostFtdcChangeAccountField","摘要","TThostFtdcDigestType", "Digest", &(m_ThostFtdcChangeAccountField.Digest));
	RegField("CThostFtdcChangeAccountField","错误代码","TThostFtdcErrorIDType", "ErrorID", &(m_ThostFtdcChangeAccountField.ErrorID));
	RegField("CThostFtdcChangeAccountField","错误信息","TThostFtdcErrorMsgType", "ErrorMsg", &(m_ThostFtdcChangeAccountField.ErrorMsg));

	RegField("CThostFtdcSecAgentACIDMapField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcSecAgentACIDMapField.BrokerID));
	RegField("CThostFtdcSecAgentACIDMapField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcSecAgentACIDMapField.UserID));
	RegField("CThostFtdcSecAgentACIDMapField","资金账户","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcSecAgentACIDMapField.AccountID));
	RegField("CThostFtdcSecAgentACIDMapField","币种","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcSecAgentACIDMapField.CurrencyID));
	RegField("CThostFtdcSecAgentACIDMapField","境外中介机构资金帐号","TThostFtdcAccountIDType", "BrokerSecAgentID", &(m_ThostFtdcSecAgentACIDMapField.BrokerSecAgentID));

	RegField("CThostFtdcQrySecAgentACIDMapField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQrySecAgentACIDMapField.BrokerID));
	RegField("CThostFtdcQrySecAgentACIDMapField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQrySecAgentACIDMapField.UserID));
	RegField("CThostFtdcQrySecAgentACIDMapField","资金账户","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcQrySecAgentACIDMapField.AccountID));
	RegField("CThostFtdcQrySecAgentACIDMapField","币种","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcQrySecAgentACIDMapField.CurrencyID));

	RegField("CThostFtdcUserRightsAssignField","应用单元代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcUserRightsAssignField.BrokerID));
	RegField("CThostFtdcUserRightsAssignField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcUserRightsAssignField.UserID));
	RegField("CThostFtdcUserRightsAssignField","交易中心代码","TThostFtdcDRIdentityIDType", "DRIdentityID", &(m_ThostFtdcUserRightsAssignField.DRIdentityID));

	RegField("CThostFtdcBrokerUserRightAssignField","应用单元代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcBrokerUserRightAssignField.BrokerID));
	RegField("CThostFtdcBrokerUserRightAssignField","交易中心代码","TThostFtdcDRIdentityIDType", "DRIdentityID", &(m_ThostFtdcBrokerUserRightAssignField.DRIdentityID));
	RegField("CThostFtdcBrokerUserRightAssignField","能否交易","TThostFtdcBoolType", "Tradeable", &(m_ThostFtdcBrokerUserRightAssignField.Tradeable));

	RegField("CThostFtdcDRTransferField","原交易中心代码","TThostFtdcDRIdentityIDType", "OrigDRIdentityID", &(m_ThostFtdcDRTransferField.OrigDRIdentityID));
	RegField("CThostFtdcDRTransferField","目标交易中心代码","TThostFtdcDRIdentityIDType", "DestDRIdentityID", &(m_ThostFtdcDRTransferField.DestDRIdentityID));
	RegField("CThostFtdcDRTransferField","原应用单元代码","TThostFtdcBrokerIDType", "OrigBrokerID", &(m_ThostFtdcDRTransferField.OrigBrokerID));
	RegField("CThostFtdcDRTransferField","目标易用单元代码","TThostFtdcBrokerIDType", "DestBrokerID", &(m_ThostFtdcDRTransferField.DestBrokerID));

	RegField("CThostFtdcFensUserInfoField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcFensUserInfoField.BrokerID));
	RegField("CThostFtdcFensUserInfoField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcFensUserInfoField.UserID));
	RegField("CThostFtdcFensUserInfoField","登录模式","TThostFtdcLoginModeType", "LoginMode", &(m_ThostFtdcFensUserInfoField.LoginMode));

	RegField("CThostFtdcCurrTransferIdentityField","交易中心代码","TThostFtdcDRIdentityIDType", "IdentityID", &(m_ThostFtdcCurrTransferIdentityField.IdentityID));

	RegField("CThostFtdcLoginForbiddenUserField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcLoginForbiddenUserField.BrokerID));
	RegField("CThostFtdcLoginForbiddenUserField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcLoginForbiddenUserField.UserID));

	RegField("CThostFtdcQryLoginForbiddenUserField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcQryLoginForbiddenUserField.BrokerID));
	RegField("CThostFtdcQryLoginForbiddenUserField","用户代码","TThostFtdcUserIDType", "UserID", &(m_ThostFtdcQryLoginForbiddenUserField.UserID));

	RegField("CThostFtdcMulticastGroupInfoField","组播组IP地址","TThostFtdcIPAddressType", "GroupIP", &(m_ThostFtdcMulticastGroupInfoField.GroupIP));
	RegField("CThostFtdcMulticastGroupInfoField","组播组IP端口","TThostFtdcIPPortType", "GroupPort", &(m_ThostFtdcMulticastGroupInfoField.GroupPort));
	RegField("CThostFtdcMulticastGroupInfoField","源地址","TThostFtdcIPAddressType", "SourceIP", &(m_ThostFtdcMulticastGroupInfoField.SourceIP));

	RegField("CThostFtdcTradingAccountReserveField","经纪公司代码","TThostFtdcBrokerIDType", "BrokerID", &(m_ThostFtdcTradingAccountReserveField.BrokerID));
	RegField("CThostFtdcTradingAccountReserveField","投资者帐号","TThostFtdcAccountIDType", "AccountID", &(m_ThostFtdcTradingAccountReserveField.AccountID));
	RegField("CThostFtdcTradingAccountReserveField","基本准备金","TThostFtdcMoneyType", "Reserve", &(m_ThostFtdcTradingAccountReserveField.Reserve));
	RegField("CThostFtdcTradingAccountReserveField","币种代码","TThostFtdcCurrencyIDType", "CurrencyID", &(m_ThostFtdcTradingAccountReserveField.CurrencyID));

}

void CFemasTHelper::InitFunctions()
{
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "客户端认证请求"), "ReqAuthenticate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqAuthenticate, m_pTraderApi, &m_ThostFtdcReqAuthenticateField, std::placeholders::_1)), "CThostFtdcReqAuthenticateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "用户登录请求"), "ReqUserLogin", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqUserLogin, m_pTraderApi, &m_ThostFtdcReqUserLoginField, std::placeholders::_1)), "CThostFtdcReqUserLoginField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "登出请求"), "ReqUserLogout", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqUserLogout, m_pTraderApi, &m_ThostFtdcUserLogoutField, std::placeholders::_1)), "CThostFtdcUserLogoutField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "用户口令更新请求"), "ReqUserPasswordUpdate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqUserPasswordUpdate, m_pTraderApi, &m_ThostFtdcUserPasswordUpdateField, std::placeholders::_1)), "CThostFtdcUserPasswordUpdateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "资金账户口令更新请求"), "ReqTradingAccountPasswordUpdate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqTradingAccountPasswordUpdate, m_pTraderApi, &m_ThostFtdcTradingAccountPasswordUpdateField, std::placeholders::_1)), "CThostFtdcTradingAccountPasswordUpdateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "报单录入请求"), "ReqOrderInsert", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqOrderInsert, m_pTraderApi, &m_ThostFtdcInputOrderField, std::placeholders::_1)), "CThostFtdcInputOrderField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "预埋单录入请求"), "ReqParkedOrderInsert", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqParkedOrderInsert, m_pTraderApi, &m_ThostFtdcParkedOrderField, std::placeholders::_1)), "CThostFtdcParkedOrderField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "预埋撤单录入请求"), "ReqParkedOrderAction", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqParkedOrderAction, m_pTraderApi, &m_ThostFtdcParkedOrderActionField, std::placeholders::_1)), "CThostFtdcParkedOrderActionField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "报单操作请求"), "ReqOrderAction", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqOrderAction, m_pTraderApi, &m_ThostFtdcInputOrderActionField, std::placeholders::_1)), "CThostFtdcInputOrderActionField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "查询最大报单数量请求"), "ReqQueryMaxOrderVolume", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQueryMaxOrderVolume, m_pTraderApi, &m_ThostFtdcQueryMaxOrderVolumeField, std::placeholders::_1)), "CThostFtdcQueryMaxOrderVolumeField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "投资者结算结果确认"), "ReqSettlementInfoConfirm", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqSettlementInfoConfirm, m_pTraderApi, &m_ThostFtdcSettlementInfoConfirmField, std::placeholders::_1)), "CThostFtdcSettlementInfoConfirmField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求删除预埋单"), "ReqRemoveParkedOrder", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqRemoveParkedOrder, m_pTraderApi, &m_ThostFtdcRemoveParkedOrderField, std::placeholders::_1)), "CThostFtdcRemoveParkedOrderField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求删除预埋撤单"), "ReqRemoveParkedOrderAction", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqRemoveParkedOrderAction, m_pTraderApi, &m_ThostFtdcRemoveParkedOrderActionField, std::placeholders::_1)), "CThostFtdcRemoveParkedOrderActionField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "执行宣告录入请求"), "ReqExecOrderInsert", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqExecOrderInsert, m_pTraderApi, &m_ThostFtdcInputExecOrderField, std::placeholders::_1)), "CThostFtdcInputExecOrderField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "执行宣告操作请求"), "ReqExecOrderAction", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqExecOrderAction, m_pTraderApi, &m_ThostFtdcInputExecOrderActionField, std::placeholders::_1)), "CThostFtdcInputExecOrderActionField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "询价录入请求"), "ReqForQuoteInsert", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqForQuoteInsert, m_pTraderApi, &m_ThostFtdcInputForQuoteField, std::placeholders::_1)), "CThostFtdcInputForQuoteField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "报价录入请求"), "ReqQuoteInsert", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQuoteInsert, m_pTraderApi, &m_ThostFtdcInputQuoteField, std::placeholders::_1)), "CThostFtdcInputQuoteField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "报价操作请求"), "ReqQuoteAction", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQuoteAction, m_pTraderApi, &m_ThostFtdcInputQuoteActionField, std::placeholders::_1)), "CThostFtdcInputQuoteActionField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询报单"), "ReqQryOrder", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryOrder, m_pTraderApi, &m_ThostFtdcQryOrderField, std::placeholders::_1)), "CThostFtdcQryOrderField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询成交"), "ReqQryTrade", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryTrade, m_pTraderApi, &m_ThostFtdcQryTradeField, std::placeholders::_1)), "CThostFtdcQryTradeField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询投资者持仓"), "ReqQryInvestorPosition", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInvestorPosition, m_pTraderApi, &m_ThostFtdcQryInvestorPositionField, std::placeholders::_1)), "CThostFtdcQryInvestorPositionField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询资金账户"), "ReqQryTradingAccount", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryTradingAccount, m_pTraderApi, &m_ThostFtdcQryTradingAccountField, std::placeholders::_1)), "CThostFtdcQryTradingAccountField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询投资者"), "ReqQryInvestor", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInvestor, m_pTraderApi, &m_ThostFtdcQryInvestorField, std::placeholders::_1)), "CThostFtdcQryInvestorField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询交易编码"), "ReqQryTradingCode", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryTradingCode, m_pTraderApi, &m_ThostFtdcQryTradingCodeField, std::placeholders::_1)), "CThostFtdcQryTradingCodeField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询合约保证金率"), "ReqQryInstrumentMarginRate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInstrumentMarginRate, m_pTraderApi, &m_ThostFtdcQryInstrumentMarginRateField, std::placeholders::_1)), "CThostFtdcQryInstrumentMarginRateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询合约手续费率"), "ReqQryInstrumentCommissionRate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInstrumentCommissionRate, m_pTraderApi, &m_ThostFtdcQryInstrumentCommissionRateField, std::placeholders::_1)), "CThostFtdcQryInstrumentCommissionRateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询交易所"), "ReqQryExchange", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryExchange, m_pTraderApi, &m_ThostFtdcQryExchangeField, std::placeholders::_1)), "CThostFtdcQryExchangeField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询产品"), "ReqQryProduct", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryProduct, m_pTraderApi, &m_ThostFtdcQryProductField, std::placeholders::_1)), "CThostFtdcQryProductField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询合约"), "ReqQryInstrument", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInstrument, m_pTraderApi, &m_ThostFtdcQryInstrumentField, std::placeholders::_1)), "CThostFtdcQryInstrumentField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询行情"), "ReqQryDepthMarketData", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryDepthMarketData, m_pTraderApi, &m_ThostFtdcQryDepthMarketDataField, std::placeholders::_1)), "CThostFtdcQryDepthMarketDataField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询投资者结算结果"), "ReqQrySettlementInfo", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQrySettlementInfo, m_pTraderApi, &m_ThostFtdcQrySettlementInfoField, std::placeholders::_1)), "CThostFtdcQrySettlementInfoField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询转帐银行"), "ReqQryTransferBank", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryTransferBank, m_pTraderApi, &m_ThostFtdcQryTransferBankField, std::placeholders::_1)), "CThostFtdcQryTransferBankField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询投资者持仓明细"), "ReqQryInvestorPositionDetail", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInvestorPositionDetail, m_pTraderApi, &m_ThostFtdcQryInvestorPositionDetailField, std::placeholders::_1)), "CThostFtdcQryInvestorPositionDetailField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询客户通知"), "ReqQryNotice", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryNotice, m_pTraderApi, &m_ThostFtdcQryNoticeField, std::placeholders::_1)), "CThostFtdcQryNoticeField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询结算信息确认"), "ReqQrySettlementInfoConfirm", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQrySettlementInfoConfirm, m_pTraderApi, &m_ThostFtdcQrySettlementInfoConfirmField, std::placeholders::_1)), "CThostFtdcQrySettlementInfoConfirmField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询投资者持仓明细"), "ReqQryInvestorPositionCombineDetail", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInvestorPositionCombineDetail, m_pTraderApi, &m_ThostFtdcQryInvestorPositionCombineDetailField, std::placeholders::_1)), "CThostFtdcQryInvestorPositionCombineDetailField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询保证金监管系统经纪公司资金账户密钥"), "ReqQryCFMMCTradingAccountKey", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryCFMMCTradingAccountKey, m_pTraderApi, &m_ThostFtdcQryCFMMCTradingAccountKeyField, std::placeholders::_1)), "CThostFtdcQryCFMMCTradingAccountKeyField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询仓单折抵信息"), "ReqQryEWarrantOffset", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryEWarrantOffset, m_pTraderApi, &m_ThostFtdcQryEWarrantOffsetField, std::placeholders::_1)), "CThostFtdcQryEWarrantOffsetField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询投资者品种/跨品种保证金"), "ReqQryInvestorProductGroupMargin", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryInvestorProductGroupMargin, m_pTraderApi, &m_ThostFtdcQryInvestorProductGroupMarginField, std::placeholders::_1)), "CThostFtdcQryInvestorProductGroupMarginField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询交易所保证金率"), "ReqQryExchangeMarginRate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryExchangeMarginRate, m_pTraderApi, &m_ThostFtdcQryExchangeMarginRateField, std::placeholders::_1)), "CThostFtdcQryExchangeMarginRateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询交易所调整保证金率"), "ReqQryExchangeMarginRateAdjust", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryExchangeMarginRateAdjust, m_pTraderApi, &m_ThostFtdcQryExchangeMarginRateAdjustField, std::placeholders::_1)), "CThostFtdcQryExchangeMarginRateAdjustField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询汇率"), "ReqQryExchangeRate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryExchangeRate, m_pTraderApi, &m_ThostFtdcQryExchangeRateField, std::placeholders::_1)), "CThostFtdcQryExchangeRateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询二级代理操作员银期权限"), "ReqQrySecAgentACIDMap", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQrySecAgentACIDMap, m_pTraderApi, &m_ThostFtdcQrySecAgentACIDMapField, std::placeholders::_1)), "CThostFtdcQrySecAgentACIDMapField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询期权交易成本"), "ReqQryOptionInstrTradeCost", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryOptionInstrTradeCost, m_pTraderApi, &m_ThostFtdcQryOptionInstrTradeCostField, std::placeholders::_1)), "CThostFtdcQryOptionInstrTradeCostField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询期权合约手续费"), "ReqQryOptionInstrCommRate", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryOptionInstrCommRate, m_pTraderApi, &m_ThostFtdcQryOptionInstrCommRateField, std::placeholders::_1)), "CThostFtdcQryOptionInstrCommRateField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询执行宣告"), "ReqQryExecOrder", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryExecOrder, m_pTraderApi, &m_ThostFtdcQryExecOrderField, std::placeholders::_1)), "CThostFtdcQryExecOrderField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询询价"), "ReqQryForQuote", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryForQuote, m_pTraderApi, &m_ThostFtdcQryForQuoteField, std::placeholders::_1)), "CThostFtdcQryForQuoteField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询报价"), "ReqQryQuote", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryQuote, m_pTraderApi, &m_ThostFtdcQryQuoteField, std::placeholders::_1)), "CThostFtdcQryQuoteField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询转帐流水"), "ReqQryTransferSerial", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryTransferSerial, m_pTraderApi, &m_ThostFtdcQryTransferSerialField, std::placeholders::_1)), "CThostFtdcQryTransferSerialField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询银期签约关系"), "ReqQryAccountregister", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryAccountregister, m_pTraderApi, &m_ThostFtdcQryAccountregisterField, std::placeholders::_1)), "CThostFtdcQryAccountregisterField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询签约银行"), "ReqQryContractBank", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryContractBank, m_pTraderApi, &m_ThostFtdcQryContractBankField, std::placeholders::_1)), "CThostFtdcQryContractBankField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询预埋单"), "ReqQryParkedOrder", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryParkedOrder, m_pTraderApi, &m_ThostFtdcQryParkedOrderField, std::placeholders::_1)), "CThostFtdcQryParkedOrderField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询预埋撤单"), "ReqQryParkedOrderAction", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryParkedOrderAction, m_pTraderApi, &m_ThostFtdcQryParkedOrderActionField, std::placeholders::_1)), "CThostFtdcQryParkedOrderActionField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询交易通知"), "ReqQryTradingNotice", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryTradingNotice, m_pTraderApi, &m_ThostFtdcQryTradingNoticeField, std::placeholders::_1)), "CThostFtdcQryTradingNoticeField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询经纪公司交易参数"), "ReqQryBrokerTradingParams", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryBrokerTradingParams, m_pTraderApi, &m_ThostFtdcQryBrokerTradingParamsField, std::placeholders::_1)), "CThostFtdcQryBrokerTradingParamsField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "请求查询经纪公司交易算法"), "ReqQryBrokerTradingAlgos", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQryBrokerTradingAlgos, m_pTraderApi, &m_ThostFtdcQryBrokerTradingAlgosField, std::placeholders::_1)), "CThostFtdcQryBrokerTradingAlgosField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "期货发起银行资金转期货请求"), "ReqFromBankToFutureByFuture", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqFromBankToFutureByFuture, m_pTraderApi, &m_ThostFtdcReqTransferField, std::placeholders::_1)), "CThostFtdcReqTransferField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "期货发起期货资金转银行请求"), "ReqFromFutureToBankByFuture", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqFromFutureToBankByFuture, m_pTraderApi, &m_ThostFtdcReqTransferField, std::placeholders::_1)), "CThostFtdcReqTransferField");
	RegFun(m_pMainDlg->m_pList->InsertString(-1, "期货发起查询银行余额请求"), "ReqQueryBankAccountMoneyByFuture", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::ReqQueryBankAccountMoneyByFuture, m_pTraderApi, &m_ThostFtdcReqQueryAccountField, std::placeholders::_1)), "CThostFtdcReqQueryAccountField");
}

void CFemasTHelper::InitTraderApi()
{
	std::string path = GetRelativePath();
	m_pTraderApi = CThostFtdcTraderApi::CreateFtdcTraderApi(path.c_str());
	m_pThostSpiHandler = new CFemasTraderSpiHandler(this);
	m_pTraderApi->RegisterSpi(m_pThostSpiHandler);
	m_pTraderApi->SubscribePrivateTopic(THOST_TERT_RESUME);
	m_pTraderApi->SubscribePublicTopic(THOST_TERT_RESUME);
	m_pTraderApi->RegisterFront("tcp://asp-sim2-front1.financial-trading-platform.com:26205");
	m_pTraderApi->Init();
}

int CFemasTHelper::GenerateReqID()
{
	return m_RequestID++;
}

std::string CFemasTHelper::GetRelativePath( const std::string &filepath )
{
	char buffer[MAX_PATH + 1];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string str = buffer;
	return str.substr(0, str.find_last_of('\\') + 1) + filepath;
}

void CFemasTHelper::AddSpiMsg( void* Handler, CThostSpiMessage * SpiMsg )
{
	if (Handler == (void*)m_pThostSpiHandler)
	{
		if (m_SpiMsgQueueSize > 256) Sleep(m_SpiMsgQueueSize / 256);
		bool b = m_pMainDlg->PostMessage(CMainDlg::MSG_THOST_SPI, (WPARAM)SpiMsg);
		InterlockedIncrement(&m_SpiMsgQueueSize);
	}
	else
	{
		delete SpiMsg;
	}
}

void CFemasTHelper::OnSpiDialogMsg( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	switch(pSpiMsg->m_MsgType)
	{
	case SPI::OnRspAuthenticate:
		OnRspAuthenticate(pSpiMsg);
		break;
	case SPI::OnRspUserLogin:
		OnRspUserLogin(pSpiMsg);
		break;
	case SPI::OnRspUserLogout:
		OnRspUserLogout(pSpiMsg);
		break;
	case SPI::OnRspUserPasswordUpdate:
		OnRspUserPasswordUpdate(pSpiMsg);
		break;
	case SPI::OnRspTradingAccountPasswordUpdate:
		OnRspTradingAccountPasswordUpdate(pSpiMsg);
		break;
	case SPI::OnRspOrderInsert:
		OnRspOrderInsert(pSpiMsg);
		break;
	case SPI::OnRspParkedOrderInsert:
		OnRspParkedOrderInsert(pSpiMsg);
		break;
	case SPI::OnRspParkedOrderAction:
		OnRspParkedOrderAction(pSpiMsg);
		break;
	case SPI::OnRspOrderAction:
		OnRspOrderAction(pSpiMsg);
		break;
	case SPI::OnRspQueryMaxOrderVolume:
		OnRspQueryMaxOrderVolume(pSpiMsg);
		break;
	case SPI::OnRspSettlementInfoConfirm:
		OnRspSettlementInfoConfirm(pSpiMsg);
		break;
	case SPI::OnRspRemoveParkedOrder:
		OnRspRemoveParkedOrder(pSpiMsg);
		break;
	case SPI::OnRspRemoveParkedOrderAction:
		OnRspRemoveParkedOrderAction(pSpiMsg);
		break;
	case SPI::OnRspExecOrderInsert:
		OnRspExecOrderInsert(pSpiMsg);
		break;
	case SPI::OnRspExecOrderAction:
		OnRspExecOrderAction(pSpiMsg);
		break;
	case SPI::OnRspForQuoteInsert:
		OnRspForQuoteInsert(pSpiMsg);
		break;
	case SPI::OnRspQuoteInsert:
		OnRspQuoteInsert(pSpiMsg);
		break;
	case SPI::OnRspQuoteAction:
		OnRspQuoteAction(pSpiMsg);
		break;
	case SPI::OnRspQryOrder:
		OnRspQryOrder(pSpiMsg);
		break;
	case SPI::OnRspQryTrade:
		OnRspQryTrade(pSpiMsg);
		break;
	case SPI::OnRspQryInvestorPosition:
		OnRspQryInvestorPosition(pSpiMsg);
		break;
	case SPI::OnRspQryTradingAccount:
		OnRspQryTradingAccount(pSpiMsg);
		break;
	case SPI::OnRspQryInvestor:
		OnRspQryInvestor(pSpiMsg);
		break;
	case SPI::OnRspQryTradingCode:
		OnRspQryTradingCode(pSpiMsg);
		break;
	case SPI::OnRspQryInstrumentMarginRate:
		OnRspQryInstrumentMarginRate(pSpiMsg);
		break;
	case SPI::OnRspQryInstrumentCommissionRate:
		OnRspQryInstrumentCommissionRate(pSpiMsg);
		break;
	case SPI::OnRspQryExchange:
		OnRspQryExchange(pSpiMsg);
		break;
	case SPI::OnRspQryProduct:
		OnRspQryProduct(pSpiMsg);
		break;
	case SPI::OnRspQryInstrument:
		OnRspQryInstrument(pSpiMsg);
		break;
	case SPI::OnRspQryDepthMarketData:
		OnRspQryDepthMarketData(pSpiMsg);
		break;
	case SPI::OnRspQrySettlementInfo:
		OnRspQrySettlementInfo(pSpiMsg);
		break;
	case SPI::OnRspQryTransferBank:
		OnRspQryTransferBank(pSpiMsg);
		break;
	case SPI::OnRspQryInvestorPositionDetail:
		OnRspQryInvestorPositionDetail(pSpiMsg);
		break;
	case SPI::OnRspQryNotice:
		OnRspQryNotice(pSpiMsg);
		break;
	case SPI::OnRspQrySettlementInfoConfirm:
		OnRspQrySettlementInfoConfirm(pSpiMsg);
		break;
	case SPI::OnRspQryInvestorPositionCombineDetail:
		OnRspQryInvestorPositionCombineDetail(pSpiMsg);
		break;
	case SPI::OnRspQryCFMMCTradingAccountKey:
		OnRspQryCFMMCTradingAccountKey(pSpiMsg);
		break;
	case SPI::OnRspQryEWarrantOffset:
		OnRspQryEWarrantOffset(pSpiMsg);
		break;
	case SPI::OnRspQryInvestorProductGroupMargin:
		OnRspQryInvestorProductGroupMargin(pSpiMsg);
		break;
	case SPI::OnRspQryExchangeMarginRate:
		OnRspQryExchangeMarginRate(pSpiMsg);
		break;
	case SPI::OnRspQryExchangeMarginRateAdjust:
		OnRspQryExchangeMarginRateAdjust(pSpiMsg);
		break;
	case SPI::OnRspQryExchangeRate:
		OnRspQryExchangeRate(pSpiMsg);
		break;
	case SPI::OnRspQrySecAgentACIDMap:
		OnRspQrySecAgentACIDMap(pSpiMsg);
		break;
	case SPI::OnRspQryOptionInstrTradeCost:
		OnRspQryOptionInstrTradeCost(pSpiMsg);
		break;
	case SPI::OnRspQryOptionInstrCommRate:
		OnRspQryOptionInstrCommRate(pSpiMsg);
		break;
	case SPI::OnRspQryExecOrder:
		OnRspQryExecOrder(pSpiMsg);
		break;
	case SPI::OnRspQryForQuote:
		OnRspQryForQuote(pSpiMsg);
		break;
	case SPI::OnRspQryQuote:
		OnRspQryQuote(pSpiMsg);
		break;
	case SPI::OnRspQryTransferSerial:
		OnRspQryTransferSerial(pSpiMsg);
		break;
	case SPI::OnRspQryAccountregister:
		OnRspQryAccountregister(pSpiMsg);
		break;
	case SPI::OnRspError:
		OnRspError(pSpiMsg);
		break;
	case SPI::OnRtnOrder:
		OnRtnOrder(pSpiMsg);
		break;
	case SPI::OnRtnTrade:
		OnRtnTrade(pSpiMsg);
		break;
	case SPI::OnErrRtnOrderInsert:
		OnErrRtnOrderInsert(pSpiMsg);
		break;
	case SPI::OnErrRtnOrderAction:
		OnErrRtnOrderAction(pSpiMsg);
		break;
	case SPI::OnRtnInstrumentStatus:
		OnRtnInstrumentStatus(pSpiMsg);
		break;
	case SPI::OnRtnTradingNotice:
		OnRtnTradingNotice(pSpiMsg);
		break;
	case SPI::OnRtnErrorConditionalOrder:
		OnRtnErrorConditionalOrder(pSpiMsg);
		break;
	case SPI::OnRtnExecOrder:
		OnRtnExecOrder(pSpiMsg);
		break;
	case SPI::OnErrRtnExecOrderInsert:
		OnErrRtnExecOrderInsert(pSpiMsg);
		break;
	case SPI::OnErrRtnExecOrderAction:
		OnErrRtnExecOrderAction(pSpiMsg);
		break;
	case SPI::OnErrRtnForQuoteInsert:
		OnErrRtnForQuoteInsert(pSpiMsg);
		break;
	case SPI::OnRtnQuote:
		OnRtnQuote(pSpiMsg);
		break;
	case SPI::OnErrRtnQuoteInsert:
		OnErrRtnQuoteInsert(pSpiMsg);
		break;
	case SPI::OnErrRtnQuoteAction:
		OnErrRtnQuoteAction(pSpiMsg);
		break;
	case SPI::OnRtnForQuoteRsp:
		OnRtnForQuoteRsp(pSpiMsg);
		break;
	case SPI::OnRspQryContractBank:
		OnRspQryContractBank(pSpiMsg);
		break;
	case SPI::OnRspQryParkedOrder:
		OnRspQryParkedOrder(pSpiMsg);
		break;
	case SPI::OnRspQryParkedOrderAction:
		OnRspQryParkedOrderAction(pSpiMsg);
		break;
	case SPI::OnRspQryTradingNotice:
		OnRspQryTradingNotice(pSpiMsg);
		break;
	case SPI::OnRspQryBrokerTradingParams:
		OnRspQryBrokerTradingParams(pSpiMsg);
		break;
	case SPI::OnRspQryBrokerTradingAlgos:
		OnRspQryBrokerTradingAlgos(pSpiMsg);
		break;
	case SPI::OnRtnFromBankToFutureByBank:
		OnRtnFromBankToFutureByBank(pSpiMsg);
		break;
	case SPI::OnRtnFromFutureToBankByBank:
		OnRtnFromFutureToBankByBank(pSpiMsg);
		break;
	case SPI::OnRtnRepealFromBankToFutureByBank:
		OnRtnRepealFromBankToFutureByBank(pSpiMsg);
		break;
	case SPI::OnRtnRepealFromFutureToBankByBank:
		OnRtnRepealFromFutureToBankByBank(pSpiMsg);
		break;
	case SPI::OnRtnFromBankToFutureByFuture:
		OnRtnFromBankToFutureByFuture(pSpiMsg);
		break;
	case SPI::OnRtnFromFutureToBankByFuture:
		OnRtnFromFutureToBankByFuture(pSpiMsg);
		break;
	case SPI::OnRtnRepealFromBankToFutureByFutureManual:
		OnRtnRepealFromBankToFutureByFutureManual(pSpiMsg);
		break;
	case SPI::OnRtnRepealFromFutureToBankByFutureManual:
		OnRtnRepealFromFutureToBankByFutureManual(pSpiMsg);
		break;
	case SPI::OnRtnQueryBankBalanceByFuture:
		OnRtnQueryBankBalanceByFuture(pSpiMsg);
		break;
	case SPI::OnErrRtnBankToFutureByFuture:
		OnErrRtnBankToFutureByFuture(pSpiMsg);
		break;
	case SPI::OnErrRtnFutureToBankByFuture:
		OnErrRtnFutureToBankByFuture(pSpiMsg);
		break;
	case SPI::OnErrRtnRepealBankToFutureByFutureManual:
		OnErrRtnRepealBankToFutureByFutureManual(pSpiMsg);
		break;
	case SPI::OnErrRtnRepealFutureToBankByFutureManual:
		OnErrRtnRepealFutureToBankByFutureManual(pSpiMsg);
		break;
	case SPI::OnErrRtnQueryBankBalanceByFuture:
		OnErrRtnQueryBankBalanceByFuture(pSpiMsg);
		break;
	case SPI::OnRtnRepealFromBankToFutureByFuture:
		OnRtnRepealFromBankToFutureByFuture(pSpiMsg);
		break;
	case SPI::OnRtnRepealFromFutureToBankByFuture:
		OnRtnRepealFromFutureToBankByFuture(pSpiMsg);
		break;
	case SPI::OnRspFromBankToFutureByFuture:
		OnRspFromBankToFutureByFuture(pSpiMsg);
		break;
	case SPI::OnRspFromFutureToBankByFuture:
		OnRspFromFutureToBankByFuture(pSpiMsg);
		break;
	case SPI::OnRspQueryBankAccountMoneyByFuture:
		OnRspQueryBankAccountMoneyByFuture(pSpiMsg);
		break;
	case SPI::OnRtnOpenAccountByBank:
		OnRtnOpenAccountByBank(pSpiMsg);
		break;
	case SPI::OnRtnCancelAccountByBank:
		OnRtnCancelAccountByBank(pSpiMsg);
		break;
	case SPI::OnRtnChangeAccountByBank:
		OnRtnChangeAccountByBank(pSpiMsg);
		break;
	default:
		break;
	}
}

void CFemasTHelper::OnThostSpiMsg( CThostSpiMessage *pSpiMsg )
{
	OnSpiDialogMsg(pSpiMsg);
	InterlockedDecrement(&m_SpiMsgQueueSize);
}

void CFemasTHelper::OnFrontConnected( CThostSpiMessage *pSpiMsg )
{
	PrintHead("客户端与交易后台建立起通信连接", "OnFrontConnected");
}

void CFemasTHelper::OnFrontDisconnected( CThostSpiMessage *pSpiMsg )
{
	PrintHead("客户端与交易后台通信连接断开", "OnFrontDisconnected");
	PrintDisconnectedReason(*(pSpiMsg->GetFieldPtr<int>()));
}


void CFemasTHelper::Init()
{
	InitMembers();
	InitTypes();
	InitFields();
	InitTraderApi();
	InitFunctions();
}

bool CFemasTHelper::ShowFields( int fid, bool bShow /*= true */ )
{
	std::string fieldstruct = m_FemasReqFuncs[fid].param1;
	int cmd = bShow?SW_SHOWNORMAL:SW_HIDE;
	for(auto it = m_Fields[fieldstruct].begin(); it != m_Fields[fieldstruct].end(); ++it)
	{
		it->h_wnd->ShowWindow(cmd);
		it->label_wnd->ShowWindow(cmd);
	}

	if (m_FemasReqFuncs[fid].parma2 != "")
	{
		fieldstruct = m_FemasReqFuncs[fid].parma2;
		for(auto it = m_Fields[fieldstruct].begin(); it != m_Fields[fieldstruct].end(); ++it)
		{
			it->h_wnd->ShowWindow(cmd);
			it->label_wnd->ShowWindow(cmd);
		}
	}
	return false;
}

void CFemasTHelper::SetTitle()
{
	std::stringstream ss;
	ss << m_RequestID;
	m_pMainDlg->SetWindowText((m_CurFunc.fname + "(" + m_CurFunc.param1 + " * , nRequestID = " + ss.str() + ")").c_str());
}

void CFemasTHelper::PrintHead( LPCTSTR Name, LPCTSTR Func )
{
	CString str;
	str.Format("\r\n %s(%s)\r\n", Name, Func);
	TV_INSERTSTRUCT TI;
	TI.hParent = m_pMainDlg->m_hRootTree;
	TI.hInsertAfter = TVI_LAST;
	TI.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	TI.item.pszText = str.GetBuffer(str.GetLength());
	TI.item.lParam = m_pMainDlg->m_nTreeItemNum++;
	m_pMainDlg->m_hCurTree = m_pMainDlg->m_pTreeOutput->InsertItem(&TI);
	m_pMainDlg->m_pTreeOutput->Expand(m_pMainDlg->m_hRootTree, TVE_EXPAND);
}

void CFemasTHelper::PrintHead( LPCTSTR Name, LPCTSTR Func, int Reqid, bool bLast )
{
	CString str;
	str.Format("\r\n %s(%s), nRequestID = %d, bLast = %d\r\n", Name, Func, Reqid, bLast);
	TV_INSERTSTRUCT TI;
	TI.hParent = m_pMainDlg->m_hRootTree;
	TI.hInsertAfter = TVI_LAST;
	TI.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	TI.item.pszText = str.GetBuffer(str.GetLength());
	TI.item.lParam = m_pMainDlg->m_nTreeItemNum++;
	m_pMainDlg->m_hCurTree = m_pMainDlg->m_pTreeOutput->InsertItem(&TI);
	m_pMainDlg->m_pTreeOutput->Expand(m_pMainDlg->m_hRootTree, TVE_EXPAND);
}

void CFemasTHelper::AppendText( LPCTSTR text )
{
	//if (m_pApiDialog->m_pCheckBox->GetCheck() == BST_CHECKED)
	//{
		TV_INSERTSTRUCT TI;
		TI.hParent = m_pMainDlg->m_hCurTree;
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		CString str = text;
		TI.item.pszText = str.GetBuffer(str.GetLength());
		TI.item.lParam = m_pMainDlg->m_nTreeItemNum++;
		m_pMainDlg->m_pTreeOutput->InsertItem(&TI);
	//}
}

int CFemasTHelper::DumpCThostFtdcField( std::string FieldName )
{
	AppendText(("[ " + FieldName + " ]\r\n").c_str());
	std::vector<Field>& fields = m_Fields[FieldName];
	for (auto it = fields.begin(); it != fields.end(); ++it)
	{
		CString text, str;
		std::string type = m_Types[it->type].ftype;
		std::string label = ( it->name + "(" + it->fname+ "):" );
		int n = 5-(label.length()-1)/8;
		for (int i = 0; i < n; i++) label+="\t";
		text += label.c_str();

		if (type == "list")
		{
			str.Format("%s", GetNameByValue(m_Types[it->type].lstrs, *(char*)it->ptr).c_str());
		}
		else if (type == "char")
		{
			str.Format("\"%s\"", (char*)it->ptr);
		}
		else if (type == "double")
		{
			if (*(double*)it->ptr < -1e40 || *(double*)it->ptr > 1e40)
			{
				str = "--";
			}
			else
			{
				str.Format("%f", *(double*)it->ptr);
			}
		}
		else	// "int"
		{
			str.Format("%d", *(int*)it->ptr);
		}
		text += str + "\r\n";
		AppendText((LPCSTR)text);
	}
	return 0;
}

void CFemasTHelper::PrintCThostFtdcRspInfoField( ThostFtdcRspInfoField *pRspInfo )
{
	if (pRspInfo)
	{
		memcpy(m_pThostFtdcRspInfoField, pRspInfo, sizeof(ThostFtdcRspInfoField));
		DumpCThostFtdcField("ThostFtdcRspInfoField");
	}
}

std::string CFemasTHelper::GetNameByValue( std::vector <std::vector<std::string> > &vec, char val )
{
	for(auto it = vec.begin(); it != vec.end(); ++it)
	{
		if ((*it)[2][0] == val)
		{
			return (*it)[0]+"("+(*it)[1]+" '"+val+"')";
		}
	}
	return std::string("未知变量") + " '"+val+"'";
}

void CFemasTHelper::PrintDisconnectedReason( int nReason )
{
	switch(nReason)
	{
	case 0x1001:
		AppendText("网络读失败");
		break;
	case 0x1002:
		AppendText("网络写失败");
		break;
	case 0x2001:
		AppendText("接收心跳超时");
		break;
	case 0x2002:
		AppendText("发送心跳失败");
		break;
	case 0x2003:
		AppendText("收到错误报文");
		break;
	default:
		AppendText("未知错误");
		break;
	}
	AppendText("\r\n");
}



void CFemasTHelper::OnRspAuthenticate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("客户端认证响应", "OnRspAuthenticate",nRequestID , bIsLast);
	CThostFtdcRspAuthenticateField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspAuthenticateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspAuthenticateField, field, sizeof(CThostFtdcRspAuthenticateField));
		DumpCThostFtdcField("CThostFtdcRspAuthenticateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspUserLogin( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("登录请求响应", "OnRspUserLogin",nRequestID , bIsLast);
	CThostFtdcRspUserLoginField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspUserLoginField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspUserLoginField, field, sizeof(CThostFtdcRspUserLoginField));
		DumpCThostFtdcField("CThostFtdcRspUserLoginField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspUserLogout( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("登出请求响应", "OnRspUserLogout",nRequestID , bIsLast);
	CThostFtdcUserLogoutField *field = pSpiMsg->GetFieldPtr<CThostFtdcUserLogoutField>();
	if (field)
	{
		memcpy(&m_ThostFtdcUserLogoutField, field, sizeof(CThostFtdcUserLogoutField));
		DumpCThostFtdcField("CThostFtdcUserLogoutField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspUserPasswordUpdate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("用户口令更新请求响应", "OnRspUserPasswordUpdate",nRequestID , bIsLast);
	CThostFtdcUserPasswordUpdateField *field = pSpiMsg->GetFieldPtr<CThostFtdcUserPasswordUpdateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcUserPasswordUpdateField, field, sizeof(CThostFtdcUserPasswordUpdateField));
		DumpCThostFtdcField("CThostFtdcUserPasswordUpdateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspTradingAccountPasswordUpdate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("资金账户口令更新请求响应", "OnRspTradingAccountPasswordUpdate",nRequestID , bIsLast);
	CThostFtdcTradingAccountPasswordUpdateField *field = pSpiMsg->GetFieldPtr<CThostFtdcTradingAccountPasswordUpdateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTradingAccountPasswordUpdateField, field, sizeof(CThostFtdcTradingAccountPasswordUpdateField));
		DumpCThostFtdcField("CThostFtdcTradingAccountPasswordUpdateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspOrderInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报单录入请求响应", "OnRspOrderInsert",nRequestID , bIsLast);
	CThostFtdcInputOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputOrderField, field, sizeof(CThostFtdcInputOrderField));
		DumpCThostFtdcField("CThostFtdcInputOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspParkedOrderInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("预埋单录入请求响应", "OnRspParkedOrderInsert",nRequestID , bIsLast);
	CThostFtdcParkedOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcParkedOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcParkedOrderField, field, sizeof(CThostFtdcParkedOrderField));
		DumpCThostFtdcField("CThostFtdcParkedOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspParkedOrderAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("预埋撤单录入请求响应", "OnRspParkedOrderAction",nRequestID , bIsLast);
	CThostFtdcParkedOrderActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcParkedOrderActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcParkedOrderActionField, field, sizeof(CThostFtdcParkedOrderActionField));
		DumpCThostFtdcField("CThostFtdcParkedOrderActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspOrderAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报单操作请求响应", "OnRspOrderAction",nRequestID , bIsLast);
	CThostFtdcInputOrderActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputOrderActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputOrderActionField, field, sizeof(CThostFtdcInputOrderActionField));
		DumpCThostFtdcField("CThostFtdcInputOrderActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQueryMaxOrderVolume( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("查询最大报单数量响应", "OnRspQueryMaxOrderVolume",nRequestID , bIsLast);
	CThostFtdcQueryMaxOrderVolumeField *field = pSpiMsg->GetFieldPtr<CThostFtdcQueryMaxOrderVolumeField>();
	if (field)
	{
		memcpy(&m_ThostFtdcQueryMaxOrderVolumeField, field, sizeof(CThostFtdcQueryMaxOrderVolumeField));
		DumpCThostFtdcField("CThostFtdcQueryMaxOrderVolumeField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspSettlementInfoConfirm( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("投资者结算结果确认响应", "OnRspSettlementInfoConfirm",nRequestID , bIsLast);
	CThostFtdcSettlementInfoConfirmField *field = pSpiMsg->GetFieldPtr<CThostFtdcSettlementInfoConfirmField>();
	if (field)
	{
		memcpy(&m_ThostFtdcSettlementInfoConfirmField, field, sizeof(CThostFtdcSettlementInfoConfirmField));
		DumpCThostFtdcField("CThostFtdcSettlementInfoConfirmField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspRemoveParkedOrder( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("删除预埋单响应", "OnRspRemoveParkedOrder",nRequestID , bIsLast);
	CThostFtdcRemoveParkedOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcRemoveParkedOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRemoveParkedOrderField, field, sizeof(CThostFtdcRemoveParkedOrderField));
		DumpCThostFtdcField("CThostFtdcRemoveParkedOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspRemoveParkedOrderAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("删除预埋撤单响应", "OnRspRemoveParkedOrderAction",nRequestID , bIsLast);
	CThostFtdcRemoveParkedOrderActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcRemoveParkedOrderActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRemoveParkedOrderActionField, field, sizeof(CThostFtdcRemoveParkedOrderActionField));
		DumpCThostFtdcField("CThostFtdcRemoveParkedOrderActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspExecOrderInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("执行宣告录入请求响应", "OnRspExecOrderInsert",nRequestID , bIsLast);
	CThostFtdcInputExecOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputExecOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputExecOrderField, field, sizeof(CThostFtdcInputExecOrderField));
		DumpCThostFtdcField("CThostFtdcInputExecOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspExecOrderAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("执行宣告操作请求响应", "OnRspExecOrderAction",nRequestID , bIsLast);
	CThostFtdcInputExecOrderActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputExecOrderActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputExecOrderActionField, field, sizeof(CThostFtdcInputExecOrderActionField));
		DumpCThostFtdcField("CThostFtdcInputExecOrderActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspForQuoteInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("询价录入请求响应", "OnRspForQuoteInsert",nRequestID , bIsLast);
	CThostFtdcInputForQuoteField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputForQuoteField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputForQuoteField, field, sizeof(CThostFtdcInputForQuoteField));
		DumpCThostFtdcField("CThostFtdcInputForQuoteField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQuoteInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报价录入请求响应", "OnRspQuoteInsert",nRequestID , bIsLast);
	CThostFtdcInputQuoteField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputQuoteField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputQuoteField, field, sizeof(CThostFtdcInputQuoteField));
		DumpCThostFtdcField("CThostFtdcInputQuoteField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQuoteAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报价操作请求响应", "OnRspQuoteAction",nRequestID , bIsLast);
	CThostFtdcInputQuoteActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputQuoteActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputQuoteActionField, field, sizeof(CThostFtdcInputQuoteActionField));
		DumpCThostFtdcField("CThostFtdcInputQuoteActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryOrder( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询报单响应", "OnRspQryOrder",nRequestID , bIsLast);
	CThostFtdcOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcOrderField, field, sizeof(CThostFtdcOrderField));
		DumpCThostFtdcField("CThostFtdcOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryTrade( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询成交响应", "OnRspQryTrade",nRequestID , bIsLast);
	CThostFtdcTradeField *field = pSpiMsg->GetFieldPtr<CThostFtdcTradeField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTradeField, field, sizeof(CThostFtdcTradeField));
		DumpCThostFtdcField("CThostFtdcTradeField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInvestorPosition( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询投资者持仓响应", "OnRspQryInvestorPosition",nRequestID , bIsLast);
	CThostFtdcInvestorPositionField *field = pSpiMsg->GetFieldPtr<CThostFtdcInvestorPositionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInvestorPositionField, field, sizeof(CThostFtdcInvestorPositionField));
		DumpCThostFtdcField("CThostFtdcInvestorPositionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryTradingAccount( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询资金账户响应", "OnRspQryTradingAccount",nRequestID , bIsLast);
	CThostFtdcTradingAccountField *field = pSpiMsg->GetFieldPtr<CThostFtdcTradingAccountField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTradingAccountField, field, sizeof(CThostFtdcTradingAccountField));
		DumpCThostFtdcField("CThostFtdcTradingAccountField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInvestor( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询投资者响应", "OnRspQryInvestor",nRequestID , bIsLast);
	CThostFtdcInvestorField *field = pSpiMsg->GetFieldPtr<CThostFtdcInvestorField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInvestorField, field, sizeof(CThostFtdcInvestorField));
		DumpCThostFtdcField("CThostFtdcInvestorField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryTradingCode( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询交易编码响应", "OnRspQryTradingCode",nRequestID , bIsLast);
	CThostFtdcTradingCodeField *field = pSpiMsg->GetFieldPtr<CThostFtdcTradingCodeField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTradingCodeField, field, sizeof(CThostFtdcTradingCodeField));
		DumpCThostFtdcField("CThostFtdcTradingCodeField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInstrumentMarginRate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询合约保证金率响应", "OnRspQryInstrumentMarginRate",nRequestID , bIsLast);
	CThostFtdcInstrumentMarginRateField *field = pSpiMsg->GetFieldPtr<CThostFtdcInstrumentMarginRateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInstrumentMarginRateField, field, sizeof(CThostFtdcInstrumentMarginRateField));
		DumpCThostFtdcField("CThostFtdcInstrumentMarginRateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInstrumentCommissionRate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询合约手续费率响应", "OnRspQryInstrumentCommissionRate",nRequestID , bIsLast);
	CThostFtdcInstrumentCommissionRateField *field = pSpiMsg->GetFieldPtr<CThostFtdcInstrumentCommissionRateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInstrumentCommissionRateField, field, sizeof(CThostFtdcInstrumentCommissionRateField));
		DumpCThostFtdcField("CThostFtdcInstrumentCommissionRateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryExchange( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询交易所响应", "OnRspQryExchange",nRequestID , bIsLast);
	CThostFtdcExchangeField *field = pSpiMsg->GetFieldPtr<CThostFtdcExchangeField>();
	if (field)
	{
		memcpy(&m_ThostFtdcExchangeField, field, sizeof(CThostFtdcExchangeField));
		DumpCThostFtdcField("CThostFtdcExchangeField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryProduct( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询产品响应", "OnRspQryProduct",nRequestID , bIsLast);
	CThostFtdcProductField *field = pSpiMsg->GetFieldPtr<CThostFtdcProductField>();
	if (field)
	{
		memcpy(&m_ThostFtdcProductField, field, sizeof(CThostFtdcProductField));
		DumpCThostFtdcField("CThostFtdcProductField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInstrument( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询合约响应", "OnRspQryInstrument",nRequestID , bIsLast);
	CThostFtdcInstrumentField *field = pSpiMsg->GetFieldPtr<CThostFtdcInstrumentField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInstrumentField, field, sizeof(CThostFtdcInstrumentField));
		DumpCThostFtdcField("CThostFtdcInstrumentField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryDepthMarketData( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询行情响应", "OnRspQryDepthMarketData",nRequestID , bIsLast);
	CThostFtdcDepthMarketDataField *field = pSpiMsg->GetFieldPtr<CThostFtdcDepthMarketDataField>();
	if (field)
	{
		memcpy(&m_ThostFtdcDepthMarketDataField, field, sizeof(CThostFtdcDepthMarketDataField));
		DumpCThostFtdcField("CThostFtdcDepthMarketDataField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQrySettlementInfo( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询投资者结算结果响应", "OnRspQrySettlementInfo",nRequestID , bIsLast);
	CThostFtdcSettlementInfoField *field = pSpiMsg->GetFieldPtr<CThostFtdcSettlementInfoField>();
	if (field)
	{
		memcpy(&m_ThostFtdcSettlementInfoField, field, sizeof(CThostFtdcSettlementInfoField));
		DumpCThostFtdcField("CThostFtdcSettlementInfoField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryTransferBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询转帐银行响应", "OnRspQryTransferBank",nRequestID , bIsLast);
	CThostFtdcTransferBankField *field = pSpiMsg->GetFieldPtr<CThostFtdcTransferBankField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTransferBankField, field, sizeof(CThostFtdcTransferBankField));
		DumpCThostFtdcField("CThostFtdcTransferBankField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInvestorPositionDetail( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询投资者持仓明细响应", "OnRspQryInvestorPositionDetail",nRequestID , bIsLast);
	CThostFtdcInvestorPositionDetailField *field = pSpiMsg->GetFieldPtr<CThostFtdcInvestorPositionDetailField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInvestorPositionDetailField, field, sizeof(CThostFtdcInvestorPositionDetailField));
		DumpCThostFtdcField("CThostFtdcInvestorPositionDetailField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryNotice( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询客户通知响应", "OnRspQryNotice",nRequestID , bIsLast);
	CThostFtdcNoticeField *field = pSpiMsg->GetFieldPtr<CThostFtdcNoticeField>();
	if (field)
	{
		memcpy(&m_ThostFtdcNoticeField, field, sizeof(CThostFtdcNoticeField));
		DumpCThostFtdcField("CThostFtdcNoticeField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQrySettlementInfoConfirm( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询结算信息确认响应", "OnRspQrySettlementInfoConfirm",nRequestID , bIsLast);
	CThostFtdcSettlementInfoConfirmField *field = pSpiMsg->GetFieldPtr<CThostFtdcSettlementInfoConfirmField>();
	if (field)
	{
		memcpy(&m_ThostFtdcSettlementInfoConfirmField, field, sizeof(CThostFtdcSettlementInfoConfirmField));
		DumpCThostFtdcField("CThostFtdcSettlementInfoConfirmField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInvestorPositionCombineDetail( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询投资者持仓明细响应", "OnRspQryInvestorPositionCombineDetail",nRequestID , bIsLast);
	CThostFtdcInvestorPositionCombineDetailField *field = pSpiMsg->GetFieldPtr<CThostFtdcInvestorPositionCombineDetailField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInvestorPositionCombineDetailField, field, sizeof(CThostFtdcInvestorPositionCombineDetailField));
		DumpCThostFtdcField("CThostFtdcInvestorPositionCombineDetailField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryCFMMCTradingAccountKey( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("查询保证金监管系统经纪公司资金账户密钥响应", "OnRspQryCFMMCTradingAccountKey",nRequestID , bIsLast);
	CThostFtdcCFMMCTradingAccountKeyField *field = pSpiMsg->GetFieldPtr<CThostFtdcCFMMCTradingAccountKeyField>();
	if (field)
	{
		memcpy(&m_ThostFtdcCFMMCTradingAccountKeyField, field, sizeof(CThostFtdcCFMMCTradingAccountKeyField));
		DumpCThostFtdcField("CThostFtdcCFMMCTradingAccountKeyField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryEWarrantOffset( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询仓单折抵信息响应", "OnRspQryEWarrantOffset",nRequestID , bIsLast);
	CThostFtdcEWarrantOffsetField *field = pSpiMsg->GetFieldPtr<CThostFtdcEWarrantOffsetField>();
	if (field)
	{
		memcpy(&m_ThostFtdcEWarrantOffsetField, field, sizeof(CThostFtdcEWarrantOffsetField));
		DumpCThostFtdcField("CThostFtdcEWarrantOffsetField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryInvestorProductGroupMargin( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询投资者品种/跨品种保证金响应", "OnRspQryInvestorProductGroupMargin",nRequestID , bIsLast);
	CThostFtdcInvestorProductGroupMarginField *field = pSpiMsg->GetFieldPtr<CThostFtdcInvestorProductGroupMarginField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInvestorProductGroupMarginField, field, sizeof(CThostFtdcInvestorProductGroupMarginField));
		DumpCThostFtdcField("CThostFtdcInvestorProductGroupMarginField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryExchangeMarginRate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询交易所保证金率响应", "OnRspQryExchangeMarginRate",nRequestID , bIsLast);
	CThostFtdcExchangeMarginRateField *field = pSpiMsg->GetFieldPtr<CThostFtdcExchangeMarginRateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcExchangeMarginRateField, field, sizeof(CThostFtdcExchangeMarginRateField));
		DumpCThostFtdcField("CThostFtdcExchangeMarginRateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryExchangeMarginRateAdjust( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询交易所调整保证金率响应", "OnRspQryExchangeMarginRateAdjust",nRequestID , bIsLast);
	CThostFtdcExchangeMarginRateAdjustField *field = pSpiMsg->GetFieldPtr<CThostFtdcExchangeMarginRateAdjustField>();
	if (field)
	{
		memcpy(&m_ThostFtdcExchangeMarginRateAdjustField, field, sizeof(CThostFtdcExchangeMarginRateAdjustField));
		DumpCThostFtdcField("CThostFtdcExchangeMarginRateAdjustField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryExchangeRate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询汇率响应", "OnRspQryExchangeRate",nRequestID , bIsLast);
	CThostFtdcExchangeRateField *field = pSpiMsg->GetFieldPtr<CThostFtdcExchangeRateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcExchangeRateField, field, sizeof(CThostFtdcExchangeRateField));
		DumpCThostFtdcField("CThostFtdcExchangeRateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQrySecAgentACIDMap( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询二级代理操作员银期权限响应", "OnRspQrySecAgentACIDMap",nRequestID , bIsLast);
	CThostFtdcSecAgentACIDMapField *field = pSpiMsg->GetFieldPtr<CThostFtdcSecAgentACIDMapField>();
	if (field)
	{
		memcpy(&m_ThostFtdcSecAgentACIDMapField, field, sizeof(CThostFtdcSecAgentACIDMapField));
		DumpCThostFtdcField("CThostFtdcSecAgentACIDMapField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryOptionInstrTradeCost( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询期权交易成本响应", "OnRspQryOptionInstrTradeCost",nRequestID , bIsLast);
	CThostFtdcOptionInstrTradeCostField *field = pSpiMsg->GetFieldPtr<CThostFtdcOptionInstrTradeCostField>();
	if (field)
	{
		memcpy(&m_ThostFtdcOptionInstrTradeCostField, field, sizeof(CThostFtdcOptionInstrTradeCostField));
		DumpCThostFtdcField("CThostFtdcOptionInstrTradeCostField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryOptionInstrCommRate( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询期权合约手续费响应", "OnRspQryOptionInstrCommRate",nRequestID , bIsLast);
	CThostFtdcOptionInstrCommRateField *field = pSpiMsg->GetFieldPtr<CThostFtdcOptionInstrCommRateField>();
	if (field)
	{
		memcpy(&m_ThostFtdcOptionInstrCommRateField, field, sizeof(CThostFtdcOptionInstrCommRateField));
		DumpCThostFtdcField("CThostFtdcOptionInstrCommRateField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryExecOrder( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询执行宣告响应", "OnRspQryExecOrder",nRequestID , bIsLast);
	CThostFtdcExecOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcExecOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcExecOrderField, field, sizeof(CThostFtdcExecOrderField));
		DumpCThostFtdcField("CThostFtdcExecOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryForQuote( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询询价响应", "OnRspQryForQuote",nRequestID , bIsLast);
	CThostFtdcForQuoteField *field = pSpiMsg->GetFieldPtr<CThostFtdcForQuoteField>();
	if (field)
	{
		memcpy(&m_ThostFtdcForQuoteField, field, sizeof(CThostFtdcForQuoteField));
		DumpCThostFtdcField("CThostFtdcForQuoteField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryQuote( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询报价响应", "OnRspQryQuote",nRequestID , bIsLast);
	CThostFtdcQuoteField *field = pSpiMsg->GetFieldPtr<CThostFtdcQuoteField>();
	if (field)
	{
		memcpy(&m_ThostFtdcQuoteField, field, sizeof(CThostFtdcQuoteField));
		DumpCThostFtdcField("CThostFtdcQuoteField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryTransferSerial( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询转帐流水响应", "OnRspQryTransferSerial",nRequestID , bIsLast);
	CThostFtdcTransferSerialField *field = pSpiMsg->GetFieldPtr<CThostFtdcTransferSerialField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTransferSerialField, field, sizeof(CThostFtdcTransferSerialField));
		DumpCThostFtdcField("CThostFtdcTransferSerialField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryAccountregister( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询银期签约关系响应", "OnRspQryAccountregister",nRequestID , bIsLast);
	CThostFtdcAccountregisterField *field = pSpiMsg->GetFieldPtr<CThostFtdcAccountregisterField>();
	if (field)
	{
		memcpy(&m_ThostFtdcAccountregisterField, field, sizeof(CThostFtdcAccountregisterField));
		DumpCThostFtdcField("CThostFtdcAccountregisterField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspError( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("错误应答", "OnRspError",nRequestID , bIsLast);
	CThostFtdcRspInfoField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspInfoField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspInfoField, field, sizeof(CThostFtdcRspInfoField));
		DumpCThostFtdcField("CThostFtdcRspInfoField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnOrder( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报单通知", "OnRtnOrder",nRequestID , bIsLast);
	CThostFtdcOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcOrderField, field, sizeof(CThostFtdcOrderField));
		DumpCThostFtdcField("CThostFtdcOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnTrade( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("成交通知", "OnRtnTrade",nRequestID , bIsLast);
	CThostFtdcTradeField *field = pSpiMsg->GetFieldPtr<CThostFtdcTradeField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTradeField, field, sizeof(CThostFtdcTradeField));
		DumpCThostFtdcField("CThostFtdcTradeField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnOrderInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报单录入错误回报", "OnErrRtnOrderInsert",nRequestID , bIsLast);
	CThostFtdcInputOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputOrderField, field, sizeof(CThostFtdcInputOrderField));
		DumpCThostFtdcField("CThostFtdcInputOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnOrderAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报单操作错误回报", "OnErrRtnOrderAction",nRequestID , bIsLast);
	CThostFtdcOrderActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcOrderActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcOrderActionField, field, sizeof(CThostFtdcOrderActionField));
		DumpCThostFtdcField("CThostFtdcOrderActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnInstrumentStatus( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("合约交易状态通知", "OnRtnInstrumentStatus",nRequestID , bIsLast);
	CThostFtdcInstrumentStatusField *field = pSpiMsg->GetFieldPtr<CThostFtdcInstrumentStatusField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInstrumentStatusField, field, sizeof(CThostFtdcInstrumentStatusField));
		DumpCThostFtdcField("CThostFtdcInstrumentStatusField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnTradingNotice( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("交易通知", "OnRtnTradingNotice",nRequestID , bIsLast);
	CThostFtdcTradingNoticeInfoField *field = pSpiMsg->GetFieldPtr<CThostFtdcTradingNoticeInfoField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTradingNoticeInfoField, field, sizeof(CThostFtdcTradingNoticeInfoField));
		DumpCThostFtdcField("CThostFtdcTradingNoticeInfoField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnErrorConditionalOrder( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("提示条件单校验错误", "OnRtnErrorConditionalOrder",nRequestID , bIsLast);
	CThostFtdcErrorConditionalOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcErrorConditionalOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcErrorConditionalOrderField, field, sizeof(CThostFtdcErrorConditionalOrderField));
		DumpCThostFtdcField("CThostFtdcErrorConditionalOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnExecOrder( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("执行宣告通知", "OnRtnExecOrder",nRequestID , bIsLast);
	CThostFtdcExecOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcExecOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcExecOrderField, field, sizeof(CThostFtdcExecOrderField));
		DumpCThostFtdcField("CThostFtdcExecOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnExecOrderInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("执行宣告录入错误回报", "OnErrRtnExecOrderInsert",nRequestID , bIsLast);
	CThostFtdcInputExecOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputExecOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputExecOrderField, field, sizeof(CThostFtdcInputExecOrderField));
		DumpCThostFtdcField("CThostFtdcInputExecOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnExecOrderAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("执行宣告操作错误回报", "OnErrRtnExecOrderAction",nRequestID , bIsLast);
	CThostFtdcExecOrderActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcExecOrderActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcExecOrderActionField, field, sizeof(CThostFtdcExecOrderActionField));
		DumpCThostFtdcField("CThostFtdcExecOrderActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnForQuoteInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("询价录入错误回报", "OnErrRtnForQuoteInsert",nRequestID , bIsLast);
	CThostFtdcInputForQuoteField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputForQuoteField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputForQuoteField, field, sizeof(CThostFtdcInputForQuoteField));
		DumpCThostFtdcField("CThostFtdcInputForQuoteField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnQuote( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报价通知", "OnRtnQuote",nRequestID , bIsLast);
	CThostFtdcQuoteField *field = pSpiMsg->GetFieldPtr<CThostFtdcQuoteField>();
	if (field)
	{
		memcpy(&m_ThostFtdcQuoteField, field, sizeof(CThostFtdcQuoteField));
		DumpCThostFtdcField("CThostFtdcQuoteField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnQuoteInsert( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报价录入错误回报", "OnErrRtnQuoteInsert",nRequestID , bIsLast);
	CThostFtdcInputQuoteField *field = pSpiMsg->GetFieldPtr<CThostFtdcInputQuoteField>();
	if (field)
	{
		memcpy(&m_ThostFtdcInputQuoteField, field, sizeof(CThostFtdcInputQuoteField));
		DumpCThostFtdcField("CThostFtdcInputQuoteField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnQuoteAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("报价操作错误回报", "OnErrRtnQuoteAction",nRequestID , bIsLast);
	CThostFtdcQuoteActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcQuoteActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcQuoteActionField, field, sizeof(CThostFtdcQuoteActionField));
		DumpCThostFtdcField("CThostFtdcQuoteActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnForQuoteRsp( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("询价通知", "OnRtnForQuoteRsp",nRequestID , bIsLast);
	CThostFtdcForQuoteRspField *field = pSpiMsg->GetFieldPtr<CThostFtdcForQuoteRspField>();
	if (field)
	{
		memcpy(&m_ThostFtdcForQuoteRspField, field, sizeof(CThostFtdcForQuoteRspField));
		DumpCThostFtdcField("CThostFtdcForQuoteRspField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryContractBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询签约银行响应", "OnRspQryContractBank",nRequestID , bIsLast);
	CThostFtdcContractBankField *field = pSpiMsg->GetFieldPtr<CThostFtdcContractBankField>();
	if (field)
	{
		memcpy(&m_ThostFtdcContractBankField, field, sizeof(CThostFtdcContractBankField));
		DumpCThostFtdcField("CThostFtdcContractBankField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryParkedOrder( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询预埋单响应", "OnRspQryParkedOrder",nRequestID , bIsLast);
	CThostFtdcParkedOrderField *field = pSpiMsg->GetFieldPtr<CThostFtdcParkedOrderField>();
	if (field)
	{
		memcpy(&m_ThostFtdcParkedOrderField, field, sizeof(CThostFtdcParkedOrderField));
		DumpCThostFtdcField("CThostFtdcParkedOrderField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryParkedOrderAction( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询预埋撤单响应", "OnRspQryParkedOrderAction",nRequestID , bIsLast);
	CThostFtdcParkedOrderActionField *field = pSpiMsg->GetFieldPtr<CThostFtdcParkedOrderActionField>();
	if (field)
	{
		memcpy(&m_ThostFtdcParkedOrderActionField, field, sizeof(CThostFtdcParkedOrderActionField));
		DumpCThostFtdcField("CThostFtdcParkedOrderActionField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryTradingNotice( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询交易通知响应", "OnRspQryTradingNotice",nRequestID , bIsLast);
	CThostFtdcTradingNoticeField *field = pSpiMsg->GetFieldPtr<CThostFtdcTradingNoticeField>();
	if (field)
	{
		memcpy(&m_ThostFtdcTradingNoticeField, field, sizeof(CThostFtdcTradingNoticeField));
		DumpCThostFtdcField("CThostFtdcTradingNoticeField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryBrokerTradingParams( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询经纪公司交易参数响应", "OnRspQryBrokerTradingParams",nRequestID , bIsLast);
	CThostFtdcBrokerTradingParamsField *field = pSpiMsg->GetFieldPtr<CThostFtdcBrokerTradingParamsField>();
	if (field)
	{
		memcpy(&m_ThostFtdcBrokerTradingParamsField, field, sizeof(CThostFtdcBrokerTradingParamsField));
		DumpCThostFtdcField("CThostFtdcBrokerTradingParamsField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQryBrokerTradingAlgos( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("请求查询经纪公司交易算法响应", "OnRspQryBrokerTradingAlgos",nRequestID , bIsLast);
	CThostFtdcBrokerTradingAlgosField *field = pSpiMsg->GetFieldPtr<CThostFtdcBrokerTradingAlgosField>();
	if (field)
	{
		memcpy(&m_ThostFtdcBrokerTradingAlgosField, field, sizeof(CThostFtdcBrokerTradingAlgosField));
		DumpCThostFtdcField("CThostFtdcBrokerTradingAlgosField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnFromBankToFutureByBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("银行发起银行资金转期货通知", "OnRtnFromBankToFutureByBank",nRequestID , bIsLast);
	CThostFtdcRspTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspTransferField, field, sizeof(CThostFtdcRspTransferField));
		DumpCThostFtdcField("CThostFtdcRspTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnFromFutureToBankByBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("银行发起期货资金转银行通知", "OnRtnFromFutureToBankByBank",nRequestID , bIsLast);
	CThostFtdcRspTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspTransferField, field, sizeof(CThostFtdcRspTransferField));
		DumpCThostFtdcField("CThostFtdcRspTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnRepealFromBankToFutureByBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("银行发起冲正银行转期货通知", "OnRtnRepealFromBankToFutureByBank",nRequestID , bIsLast);
	CThostFtdcRspRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspRepealField, field, sizeof(CThostFtdcRspRepealField));
		DumpCThostFtdcField("CThostFtdcRspRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnRepealFromFutureToBankByBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("银行发起冲正期货转银行通知", "OnRtnRepealFromFutureToBankByBank",nRequestID , bIsLast);
	CThostFtdcRspRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspRepealField, field, sizeof(CThostFtdcRspRepealField));
		DumpCThostFtdcField("CThostFtdcRspRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnFromBankToFutureByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起银行资金转期货通知", "OnRtnFromBankToFutureByFuture",nRequestID , bIsLast);
	CThostFtdcRspTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspTransferField, field, sizeof(CThostFtdcRspTransferField));
		DumpCThostFtdcField("CThostFtdcRspTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnFromFutureToBankByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起期货资金转银行通知", "OnRtnFromFutureToBankByFuture",nRequestID , bIsLast);
	CThostFtdcRspTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspTransferField, field, sizeof(CThostFtdcRspTransferField));
		DumpCThostFtdcField("CThostFtdcRspTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnRepealFromBankToFutureByFutureManual( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知", "OnRtnRepealFromBankToFutureByFutureManual",nRequestID , bIsLast);
	CThostFtdcRspRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspRepealField, field, sizeof(CThostFtdcRspRepealField));
		DumpCThostFtdcField("CThostFtdcRspRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnRepealFromFutureToBankByFutureManual( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知", "OnRtnRepealFromFutureToBankByFutureManual",nRequestID , bIsLast);
	CThostFtdcRspRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspRepealField, field, sizeof(CThostFtdcRspRepealField));
		DumpCThostFtdcField("CThostFtdcRspRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnQueryBankBalanceByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起查询银行余额通知", "OnRtnQueryBankBalanceByFuture",nRequestID , bIsLast);
	CThostFtdcNotifyQueryAccountField *field = pSpiMsg->GetFieldPtr<CThostFtdcNotifyQueryAccountField>();
	if (field)
	{
		memcpy(&m_ThostFtdcNotifyQueryAccountField, field, sizeof(CThostFtdcNotifyQueryAccountField));
		DumpCThostFtdcField("CThostFtdcNotifyQueryAccountField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnBankToFutureByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起银行资金转期货错误回报", "OnErrRtnBankToFutureByFuture",nRequestID , bIsLast);
	CThostFtdcReqTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqTransferField, field, sizeof(CThostFtdcReqTransferField));
		DumpCThostFtdcField("CThostFtdcReqTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnFutureToBankByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起期货资金转银行错误回报", "OnErrRtnFutureToBankByFuture",nRequestID , bIsLast);
	CThostFtdcReqTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqTransferField, field, sizeof(CThostFtdcReqTransferField));
		DumpCThostFtdcField("CThostFtdcReqTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnRepealBankToFutureByFutureManual( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("系统运行时期货端手工发起冲正银行转期货错误回报", "OnErrRtnRepealBankToFutureByFutureManual",nRequestID , bIsLast);
	CThostFtdcReqRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqRepealField, field, sizeof(CThostFtdcReqRepealField));
		DumpCThostFtdcField("CThostFtdcReqRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnRepealFutureToBankByFutureManual( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("系统运行时期货端手工发起冲正期货转银行错误回报", "OnErrRtnRepealFutureToBankByFutureManual",nRequestID , bIsLast);
	CThostFtdcReqRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqRepealField, field, sizeof(CThostFtdcReqRepealField));
		DumpCThostFtdcField("CThostFtdcReqRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnErrRtnQueryBankBalanceByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起查询银行余额错误回报", "OnErrRtnQueryBankBalanceByFuture",nRequestID , bIsLast);
	CThostFtdcReqQueryAccountField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqQueryAccountField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqQueryAccountField, field, sizeof(CThostFtdcReqQueryAccountField));
		DumpCThostFtdcField("CThostFtdcReqQueryAccountField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnRepealFromBankToFutureByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知", "OnRtnRepealFromBankToFutureByFuture",nRequestID , bIsLast);
	CThostFtdcRspRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspRepealField, field, sizeof(CThostFtdcRspRepealField));
		DumpCThostFtdcField("CThostFtdcRspRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnRepealFromFutureToBankByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知", "OnRtnRepealFromFutureToBankByFuture",nRequestID , bIsLast);
	CThostFtdcRspRepealField *field = pSpiMsg->GetFieldPtr<CThostFtdcRspRepealField>();
	if (field)
	{
		memcpy(&m_ThostFtdcRspRepealField, field, sizeof(CThostFtdcRspRepealField));
		DumpCThostFtdcField("CThostFtdcRspRepealField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspFromBankToFutureByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起银行资金转期货应答", "OnRspFromBankToFutureByFuture",nRequestID , bIsLast);
	CThostFtdcReqTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqTransferField, field, sizeof(CThostFtdcReqTransferField));
		DumpCThostFtdcField("CThostFtdcReqTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspFromFutureToBankByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起期货资金转银行应答", "OnRspFromFutureToBankByFuture",nRequestID , bIsLast);
	CThostFtdcReqTransferField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqTransferField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqTransferField, field, sizeof(CThostFtdcReqTransferField));
		DumpCThostFtdcField("CThostFtdcReqTransferField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRspQueryBankAccountMoneyByFuture( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("期货发起查询银行余额应答", "OnRspQueryBankAccountMoneyByFuture",nRequestID , bIsLast);
	CThostFtdcReqQueryAccountField *field = pSpiMsg->GetFieldPtr<CThostFtdcReqQueryAccountField>();
	if (field)
	{
		memcpy(&m_ThostFtdcReqQueryAccountField, field, sizeof(CThostFtdcReqQueryAccountField));
		DumpCThostFtdcField("CThostFtdcReqQueryAccountField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnOpenAccountByBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("银行发起银期开户通知", "OnRtnOpenAccountByBank",nRequestID , bIsLast);
	CThostFtdcOpenAccountField *field = pSpiMsg->GetFieldPtr<CThostFtdcOpenAccountField>();
	if (field)
	{
		memcpy(&m_ThostFtdcOpenAccountField, field, sizeof(CThostFtdcOpenAccountField));
		DumpCThostFtdcField("CThostFtdcOpenAccountField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnCancelAccountByBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("银行发起银期销户通知", "OnRtnCancelAccountByBank",nRequestID , bIsLast);
	CThostFtdcCancelAccountField *field = pSpiMsg->GetFieldPtr<CThostFtdcCancelAccountField>();
	if (field)
	{
		memcpy(&m_ThostFtdcCancelAccountField, field, sizeof(CThostFtdcCancelAccountField));
		DumpCThostFtdcField("CThostFtdcCancelAccountField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

void CFemasTHelper::OnRtnChangeAccountByBank( CThostSpiMessage *pSpiMsg )
{
	int nRequestID = pSpiMsg->m_RequestID;
	bool bIsLast = pSpiMsg->m_bIsLast;
	PrintHead("银行发起变更银行账号通知", "OnRtnChangeAccountByBank",nRequestID , bIsLast);
	CThostFtdcChangeAccountField *field = pSpiMsg->GetFieldPtr<CThostFtdcChangeAccountField>();
	if (field)
	{
		memcpy(&m_ThostFtdcChangeAccountField, field, sizeof(CThostFtdcChangeAccountField));
		DumpCThostFtdcField("CThostFtdcChangeAccountField");
	}
	PrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);
}

