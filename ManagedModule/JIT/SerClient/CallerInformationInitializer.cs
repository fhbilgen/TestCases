using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    public class CallerInformationInitializer
    {
        [ThreadStatic]
        private static RequestCallContext _currentContext;

        internal static RequestCallContext Current
        {
            get
            {
                return _currentContext ?? (_currentContext = new RequestCallContext());
            }
        }

        internal static OperationActionContext OperationActionContext
        {
            get
            {
                return Current.OperationActionContext;
            }
            set
            {
                Current.OperationActionContext = value;
            }
        }

        internal static HostSyncronizationContext HostSyncronizationContext
        {
            get
            {
                return Current.HostSyncronizationContext;
            }
            set
            {
                Current.HostSyncronizationContext = value;
            }
        }

        public static string UserCode
        {
            get
            {
                return Current.UserCode;
            }
            set
            {
                Current.UserCode = value;
            }
        }

        public static string ScreenCode
        {
            get
            {
                return Current.ScreenCode;
            }
            set
            {
                Current.ScreenCode = value;
            }
        }

        public static string BranchCode
        {
            get
            {
                return Current.BranchCode;
            }
            set
            {
                Current.BranchCode = value;
            }
        }

        public static string UnitCode
        {
            get
            {
                return Current.UnitCode;
            }
            set
            {
                Current.UnitCode = value;
            }
        }

        public static Channels Channel
        {
            get
            {
                return Current.Channel;
            }
            set
            {
                Current.Channel = value;
            }
        }

        public static string SessionId
        {
            get
            {
                return Current.SessionId;
            }
            set
            {
                Current.SessionId = value;
            }
        }

        public static string TerminalId
        {
            get
            {
                return Current.TerminalId;
            }
            set
            {
                Current.TerminalId = value;
            }
        }

        public static Guid UserSessionId
        {
            get
            {
                return Current.UserSessionId;
            }
            set
            {
                Current.UserSessionId = value;
            }
        }

        public static byte[] RequestHashCode
        {
            get
            {
                return Current.RequestHashCode;
            }
            set
            {
                Current.RequestHashCode = value;
            }
        }

        public static Languages Language
        {
            get
            {
                return Current.Language;
            }
            set
            {
                Current.Language = value;
            }
        }

        public static Guid RequestObjectId
        {
            get
            {
                return Current.RequestObjectId;
            }
            set
            {
                Current.RequestObjectId = value;
            }
        }

        public static long QueueTicketId
        {
            get
            {
                return Current.QueueTicketId;
            }
            set
            {
                Current.QueueTicketId = value;
            }
        }

        public static string CompanyInfo
        {
            get
            {
                return Current.CompanyInfo;
            }
            set
            {
                Current.CompanyInfo = value;
            }
        }

        public static bool IsInTestContext
        {
            get
            {
                return Current.IsInTestContext;
            }
            set
            {
                Current.IsInTestContext = value;
            }
        }

        public static bool AutoRollback
        {
            get
            {
                return Current.AutoRollback;
            }
        }

        public static bool BypassWorkflowOperation
        {
            get
            {
                return Current.BypassWorkflowOperation;
            }
        }

        public static string UserPassword
        {
            get
            {
                return Current.UserPassword;
            }
            set
            {
                throw new NotSupportedException("Password cannot be set");
            }
        }

        //public static List<LDTOIntegrationServiceDetail> IntegrationServiceAddresses
        //{
        //    get
        //    {
        //        return Current.IntegrationServiceAddresses;
        //    }
        //    set
        //    {
        //        Current.IntegrationServiceAddresses = value;
        //    }
        //}

        public static string IntegrationServiceAddress
        {
            get
            {
                return Current.IntegrationServiceAddress;
            }
            set
            {
                Current.IntegrationServiceAddress = value;
            }
        }

        public static string IntegrationSecondaryServiceAddress
        {
            get
            {
                return Current.IntegrationSecondaryServiceAddress;
            }
            set
            {
                Current.IntegrationSecondaryServiceAddress = value;
            }
        }

        public static bool IntegrationServiceLogEnabled
        {
            get
            {
                if (Current.IntegrationServiceLogEnabled.HasValue)
                {
                    return Current.IntegrationServiceLogEnabled.Value;
                }
                return false;
            }
            set
            {
                Current.IntegrationServiceLogEnabled = value;
            }
        }

        public static string IntegrationServiceUserName
        {
            get
            {
                return Current.IntegrationServiceUserName;
            }
            set
            {
                Current.IntegrationServiceUserName = value;
            }
        }

        public static string IntegrationServicePort
        {
            get
            {
                return Current.IntegrationServicePort;
            }
            set
            {
                Current.IntegrationServicePort = value;
            }
        }

        public static string IntegrationServiceProtocol
        {
            get
            {
                return Current.IntegrationServiceProtocol;
            }
            set
            {
                Current.IntegrationServiceProtocol = value;
            }
        }

        public static bool IsIntegrationServiceProtocol10
        {
            get
            {
                return Current.IsIntegrationServiceProtocol10;
            }
            set
            {
                Current.IsIntegrationServiceProtocol10 = value;
            }
        }

        public static bool IsIntegrationServiceProtocol11
        {
            get
            {
                return Current.IsIntegrationServiceProtocol11;
            }
            set
            {
                Current.IsIntegrationServiceProtocol11 = value;
            }
        }

        public static bool IsIntegrationServiceProtocol12
        {
            get
            {
                return Current.IsIntegrationServiceProtocol12;
            }
            set
            {
                Current.IsIntegrationServiceProtocol12 = value;
            }
        }

        public static string IntegrationServicePassword
        {
            get
            {
                return Current.IntegrationServicePassword;
            }
            set
            {
                Current.IntegrationServicePassword = value;
            }
        }

        public static long TransactionObjectId
        {
            get
            {
                return Current.TransactionObjectId;
            }
            set
            {
                Current.TransactionObjectId = value;
            }
        }

        public static bool HasHostOperationCall
        {
            get
            {
                return Current.HasHostOperationCall;
            }
            set
            {
                Current.HasHostOperationCall = value;
            }
        }

        public static Guid MainRequestObjectId
        {
            get
            {
                Guid mainRequestObjectId = Current.MainRequestObjectId;
                if (!(mainRequestObjectId == Guid.Empty))
                {
                    return mainRequestObjectId;
                }
                return Current.RequestObjectId;
            }
            set
            {
                Current.MainRequestObjectId = value;
            }
        }

        public static long DatabaseOperationCount
        {
            get
            {
                return Current.DatabaseOperationCount;
            }
            set
            {
                Current.DatabaseOperationCount = value;
            }
        }

        public static long HostOperationCount
        {
            get
            {
                return Current.HostOperationCount;
            }
            set
            {
                Current.HostOperationCount = value;
            }
        }

        public static double HostOperationsTotal
        {
            get
            {
                return Current.HostOperationsTotal;
            }
            set
            {
                Current.HostOperationsTotal = value;
            }
        }

        public static double DatabaseOperationsTotal
        {
            get
            {
                return Current.DatabaseOperationsTotal;
            }
            set
            {
                Current.DatabaseOperationsTotal = value;
            }
        }

        public static int OutboundOperationsTotal
        {
            get
            {
                return Current.OutboundOperationsTotal;
            }
            set
            {
                Current.OutboundOperationsTotal = value;
            }
        }

        public static int HostRequestLength
        {
            get
            {
                return Current.HostRequestLength;
            }
            set
            {
                Current.HostRequestLength = value;
            }
        }

        public static int HostResponseLength
        {
            get
            {
                return Current.HostResponseLength;
            }
            set
            {
                Current.HostResponseLength = value;
            }
        }

        public static string ChannelSessionId
        {
            get
            {
                return Current.ChannelSessionId;
            }
            set
            {
                Current.ChannelSessionId = value;
            }
        }

        public static string ClientIp
        {
            get
            {
                return Current.ClientIp;
            }
            set
            {
                Current.ClientIp = value;
            }
        }

        public static string CallerServerIp
        {
            get
            {
                return Current.CallerServerIp;
            }
            set
            {
                Current.CallerServerIp = value;
            }
        }

        public static string AccessToken
        {
            get
            {
                return Current.AccessToken;
            }
            set
            {
                Current.AccessToken = value;
            }
        }

        public static string ServiceInterface
        {
            get
            {
                return Current.ServiceInterface;
            }
            set
            {
                Current.ServiceInterface = value;
            }
        }

        public static string Operation
        {
            get
            {
                return Current.OperationName;
            }
            set
            {
                Current.OperationName = value;
            }
        }

        public static int CommitTime
        {
            get
            {
                return Current.CommitTime;
            }
            set
            {
                Current.CommitTime = value;
            }
        }

        public static string OperationKey
        {
            get
            {
                return Current.OperationKey;
            }
        }

        public static string ServiceName
        {
            get
            {
                return Current.ServiceName;
            }
        }

        //public static CRUDTypes OperationCrudType
        //{
        //    get
        //    {
        //        return Current.OperationCrudType;
        //    }
        //    set
        //    {
        //        Current.OperationCrudType = value;
        //    }
        //}

        public static List<object> SessionInitilizedConnections
        {
            get
            {
                return Current.SessionInitilizedConnections ?? (Current.SessionInitilizedConnections = new List<object>());
            }
            set
            {
                Current.SessionInitilizedConnections = value;
            }
        }

        public static int RaiseEventCount
        {
            get
            {
                return Current.RaiseEventCount;
            }
            set
            {
                Current.RaiseEventCount = value;
            }
        }

        //public static WorkflowInfo ApprovedWorkflowInfo
        //{
        //    get
        //    {
        //        return Current.ApprovedWorkflowInfo;
        //    }
        //    set
        //    {
        //        Current.ApprovedWorkflowInfo = value;
        //    }
        //}

        public static List<KeyValuePair<Guid, string>> ExternalServiceTrace
        {
            get
            {
                return Current.ExternalServiceTrace;
            }
            set
            {
                Current.ExternalServiceTrace = value;
            }
        }

        public static int OpenTimeout
        {
            get
            {
                return Current.OpenTimeout;
            }
            set
            {
                Current.OpenTimeout = value;
            }
        }

        public static int OperationTimeout
        {
            get
            {
                return Current.OperationTimeout;
            }
            set
            {
                Current.OperationTimeout = value;
            }
        }

        //public static Environments Environment
        //{
        //    get
        //    {
        //        return Current.Environment;
        //    }
        //    set
        //    {
        //        Current.Environment = value;
        //    }
        //}

        public static bool VirtualAddressActive
        {
            get
            {
                return Current.VirtualAddressActive;
            }
            set
            {
                Current.VirtualAddressActive = value;
            }
        }

        public static string VirtualAddress
        {
            get
            {
                return Current.VirtualAddress;
            }
            set
            {
                Current.VirtualAddress = value;
            }
        }

        public static bool IsReceiptMaskEnabled
        {
            get
            {
                return Current.IsReceiptMaskEnabled;
            }
            set
            {
                Current.IsReceiptMaskEnabled = value;
            }
        }

        public static double ConnectionOpenTime
        {
            get
            {
                return Current.ConnectionOpenTime;
            }
            set
            {
                Current.ConnectionOpenTime = value;
            }
        }

        public static void SetCurrentContext(RequestCallContext context)
        {
            _currentContext = context;
        }

        public static RequestCallContext CopyCurrentContext()
        {
            return CopyCurrentContext(false);
        }

        public static RequestCallContext CopyCurrentContext(bool includeStatistics)
        {
            return (RequestCallContext)Current.Clone(includeStatistics);
        }

        public static void ClearCurrent()
        {
            _currentContext = null;
        }
    }

}
