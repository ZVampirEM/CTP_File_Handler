#pragma once
#include <vector>
#include <string>

struct ThostFtdcRspInfoField
{
	int ErrorID;
	char ErrorMsg[81];
};
class CThostSpiMessage
	{
	public:
		enum MSG_TYPE
		{
			//====================== API_MSG_TYPE ======================
			OnRspAuthenticate,
			OnRspUserLogin,
			OnRspUserLogout,
			OnRspUserPasswordUpdate,
			OnRspTradingAccountPasswordUpdate,
			OnRspOrderInsert,
			OnRspParkedOrderInsert,
			OnRspParkedOrderAction,
			OnRspOrderAction,
			OnRspQueryMaxOrderVolume,
			OnRspSettlementInfoConfirm,
			OnRspRemoveParkedOrder,
			OnRspRemoveParkedOrderAction,
			OnRspExecOrderInsert,
			OnRspExecOrderAction,
			OnRspForQuoteInsert,
			OnRspQuoteInsert,
			OnRspQuoteAction,
			OnRspQryOrder,
			OnRspQryTrade,
			OnRspQryInvestorPosition,
			OnRspQryTradingAccount,
			OnRspQryInvestor,
			OnRspQryTradingCode,
			OnRspQryInstrumentMarginRate,
			OnRspQryInstrumentCommissionRate,
			OnRspQryExchange,
			OnRspQryProduct,
			OnRspQryInstrument,
			OnRspQryDepthMarketData,
			OnRspQrySettlementInfo,
			OnRspQryTransferBank,
			OnRspQryInvestorPositionDetail,
			OnRspQryNotice,
			OnRspQrySettlementInfoConfirm,
			OnRspQryInvestorPositionCombineDetail,
			OnRspQryCFMMCTradingAccountKey,
			OnRspQryEWarrantOffset,
			OnRspQryInvestorProductGroupMargin,
			OnRspQryExchangeMarginRate,
			OnRspQryExchangeMarginRateAdjust,
			OnRspQryExchangeRate,
			OnRspQrySecAgentACIDMap,
			OnRspQryOptionInstrTradeCost,
			OnRspQryOptionInstrCommRate,
			OnRspQryExecOrder,
			OnRspQryForQuote,
			OnRspQryQuote,
			OnRspQryTransferSerial,
			OnRspQryAccountregister,
			OnRspError,
			OnRtnOrder,
			OnRtnTrade,
			OnErrRtnOrderInsert,
			OnErrRtnOrderAction,
			OnRtnInstrumentStatus,
			OnRtnTradingNotice,
			OnRtnErrorConditionalOrder,
			OnRtnExecOrder,
			OnErrRtnExecOrderInsert,
			OnErrRtnExecOrderAction,
			OnErrRtnForQuoteInsert,
			OnRtnQuote,
			OnErrRtnQuoteInsert,
			OnErrRtnQuoteAction,
			OnRtnForQuoteRsp,
			OnRspQryContractBank,
			OnRspQryParkedOrder,
			OnRspQryParkedOrderAction,
			OnRspQryTradingNotice,
			OnRspQryBrokerTradingParams,
			OnRspQryBrokerTradingAlgos,
			OnRtnFromBankToFutureByBank,
			OnRtnFromFutureToBankByBank,
			OnRtnRepealFromBankToFutureByBank,
			OnRtnRepealFromFutureToBankByBank,
			OnRtnFromBankToFutureByFuture,
			OnRtnFromFutureToBankByFuture,
			OnRtnRepealFromBankToFutureByFutureManual,
			OnRtnRepealFromFutureToBankByFutureManual,
			OnRtnQueryBankBalanceByFuture,
			OnErrRtnBankToFutureByFuture,
			OnErrRtnFutureToBankByFuture,
			OnErrRtnRepealBankToFutureByFutureManual,
			OnErrRtnRepealFutureToBankByFutureManual,
			OnErrRtnQueryBankBalanceByFuture,
			OnRtnRepealFromBankToFutureByFuture,
			OnRtnRepealFromFutureToBankByFuture,
			OnRspFromBankToFutureByFuture,
			OnRspFromFutureToBankByFuture,
			OnRspQueryBankAccountMoneyByFuture,
			OnRtnOpenAccountByBank,
			OnRtnCancelAccountByBank,
			OnRtnChangeAccountByBank,
			//====================== API_MSG_TYPE ======================
		};

		template<class T>
		CThostSpiMessage(MSG_TYPE MsgType, const T *pThostFtdcSpiField = NULL, const ThostFtdcRspInfoField *pRspInfo = NULL, int RequestId = 0, bool bIsLast = 1)
			: m_MsgType(MsgType)
			, m_RequestID(RequestId)
			, m_bIsLast(bIsLast)
		{
			if (pRspInfo)
			{
				memcpy(&m_RspInfo, pRspInfo, sizeof(m_RspInfo));
			}
			else
			{
				memset(&m_RspInfo, 0, sizeof(m_RspInfo));
			}

			if (pThostFtdcSpiField)
			{
				m_ThostFtdcSpiField = new T;
				m_ThostFtdcSpiFieldLength = sizeof(T);
				memcpy(m_ThostFtdcSpiField, pThostFtdcSpiField, sizeof(T));
			}
			else
			{
				m_ThostFtdcSpiField = NULL;
				m_ThostFtdcSpiFieldLength = 0;
			}
		}
		~CThostSpiMessage()
		{
			if(m_ThostFtdcSpiField)
			{
				delete m_ThostFtdcSpiField;
			}
		}

		template <typename TargetT>
		TargetT *GetFieldPtr()
		{
			if (!m_ThostFtdcSpiField)
			{
				return NULL;
			}
			ATLASSERT(sizeof(TargetT) == m_ThostFtdcSpiFieldLength);
			return reinterpret_cast<TargetT*>(m_ThostFtdcSpiField);
		}

		MSG_TYPE				m_MsgType;
		void*					m_ThostFtdcSpiField;
		unsigned long			m_ThostFtdcSpiFieldLength;

		int						m_RequestID;
		bool					m_bIsLast;
		ThostFtdcRspInfoField	m_RspInfo;
	};

	class CThostSpiMessagePack : public std::vector<CThostSpiMessage *>
	{
	public:

		CThostSpiMessagePack()
		{
		}

		~CThostSpiMessagePack()
		{
			vector<CThostSpiMessage *>::iterator it;
			int sizet = size();
			for (it = begin(); it != end(); ++it)
			{
				delete *it;
			}
		}
		CThostSpiMessage::MSG_TYPE GetType(void) const
		{
			ATLASSERT(!empty());
			return (*begin())->m_MsgType;
		}
		int GetRequestID(void) const
		{
			ATLASSERT(!empty());
			return (*begin())->m_RequestID;
		}
		int GetErrorID(void) const
		{
			ATLASSERT(!empty());
			return (*begin())->m_RspInfo.ErrorID;
		}
		std::string GetErrorMsg(void) const
		{
			ATLASSERT(!empty());
			return (*begin())->m_RspInfo.ErrorMsg;
		}

		void Add(CThostSpiMessage * msg)
		{
			push_back(msg);
		}

		template <typename T>
		T *GetFieldPtr() const
		{
			assert(size() == 1);
			return (*begin())->GetFieldPtr<T>();
		}

		template <typename T>
		vector<const T *> GetAllFieldPtr() const
		{
			vector<const T *> ptrs;

			T * field = NULL;

			vector<CThostSpiMessage *>::const_iterator it;
			for (it = begin(); it != end(); ++it)
			{
				field = (*it)->GetFieldPtr<T>();
				if (field)
				{
					ptrs.push_back(field);
				}
			}
			return ptrs;
		}
	};

	typedef CThostSpiMessage SPI;

