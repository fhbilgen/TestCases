using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    public static class CallerInformation
    {
        public static string UserCode
        {
            get
            {
                return CallerInformationInitializer.UserCode;
            }
        }

        public static string ScreenCode
        {
            get
            {
                return CallerInformationInitializer.ScreenCode;
            }
        }

        public static string BranchCode
        {
            get
            {
                return CallerInformationInitializer.BranchCode;
            }
        }

        public static string UnitCode
        {
            get
            {
                return CallerInformationInitializer.UnitCode;
            }
        }

        public static Channels Channel
        {
            get
            {
                return CallerInformationInitializer.Channel;
            }
        }

        public static Guid RequestObjectId
        {
            get
            {
                return CallerInformationInitializer.RequestObjectId;
            }
        }

        public static Guid MainRequestObjectId
        {
            get
            {
                return CallerInformationInitializer.MainRequestObjectId;
            }
        }

        public static List<string> ExternalServiceTrace
        {
            get
            {
                return CallerInformationInitializer.ExternalServiceTrace.Select((KeyValuePair<Guid, string> i) => i.Value).ToList();
            }
        }

        public static string SessionId
        {
            get
            {
                return CallerInformationInitializer.SessionId;
            }
        }

        public static string TerminalId
        {
            get
            {
                return CallerInformationInitializer.TerminalId;
            }
        }

        public static string ClientIp
        {
            get
            {
                return CallerInformationInitializer.ClientIp;
            }
        }

        public static string CallerServerIp
        {
            get
            {
                return CallerInformationInitializer.CallerServerIp;
            }
        }

        public static string AccessToken
        {
            get
            {
                return CallerInformationInitializer.AccessToken;
            }
        }

        public static Guid UserSessionId
        {
            get
            {
                return CallerInformationInitializer.UserSessionId;
            }
        }

        public static byte[] RequestHashCode
        {
            get
            {
                return CallerInformationInitializer.RequestHashCode;
            }
        }

        public static Languages Language
        {
            get
            {
                return CallerInformationInitializer.Language;
            }
        }

        public static string UserPassword
        {
            get
            {
                return CallerInformationInitializer.UserPassword;
            }
        }

        public static long TransactionObjectId
        {
            get
            {
                return CallerInformationInitializer.TransactionObjectId;
            }
        }

        public static long QueueTicketId
        {
            get
            {
                return CallerInformationInitializer.QueueTicketId;
            }
        }

        public static string CompanyInfo
        {
            get
            {
                return CallerInformationInitializer.CompanyInfo;
            }
        }

        public static bool HasHostOperationCall
        {
            get
            {
                return CallerInformationInitializer.HasHostOperationCall;
            }
            set
            {
                CallerInformationInitializer.HasHostOperationCall = value;
            }
        }

        public static string ChannelSessionId
        {
            get
            {
                return CallerInformationInitializer.ChannelSessionId;
            }
        }

        public static bool IsReceiptMaskEnabled
        {
            get
            {
                return CallerInformationInitializer.IsReceiptMaskEnabled;
            }
        }

        public static double ConnectionOpenTime
        {
            get
            {
                return CallerInformationInitializer.ConnectionOpenTime;
            }
        }

        public static void SetChannel(Channels channel)
        {
            CallerInformationInitializer.Channel = channel;
        }
    }

}
