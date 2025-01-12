using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    [Serializable]
    [DataContract]
    public class RequestCallContext : ICloneable
    {
        private List<KeyValuePair<Guid, string>> _externalServiceTrace;

        public long HostOperationCount { get; set; }

        public double HostOperationsTotal { get; set; }

        public bool HasHostOperationCall { get; set; }

        public string ScreenCode { get; set; }

        public string UserCode { get; set; }

        public Channels Channel { get; set; }

        public string BranchCode { get; set; }

        public string UnitCode { get; set; }

        public Guid RequestObjectId { get; set; }

        public string SessionId { get; set; }

        public Guid UserSessionId { get; set; }

        public byte[] RequestHashCode { get; set; }

        public string TerminalId { get; set; }

        public Languages Language { get; set; }

        public string UserPassword { get; set; }

        public string IntegrationServicePassword { get; set; }

        public string IntegrationServiceUserName { get; set; }

        public string IntegrationServicePort { get; set; }

        public string IntegrationServiceProtocol { get; set; }

        public bool IsIntegrationServiceProtocol10 { get; set; }

        public bool IsIntegrationServiceProtocol11 { get; set; }

        public bool IsIntegrationServiceProtocol12 { get; set; }

        //public List<LDTOIntegrationServiceDetail> IntegrationServiceAddresses { get; set; }

        public string IntegrationServiceAddress { get; set; }

        public string IntegrationSecondaryServiceAddress { get; set; }

        public bool? IntegrationServiceLogEnabled { get; set; }

        public int OpenTimeout { get; set; }

        public int OperationTimeout { get; set; }

        //public Environments Environment { get; set; }

        public double ConnectionOpenTime { get; set; }

        public object ThisLock
        {
            get
            {
                return this;
            }
        }

        public Guid MainRequestObjectId { get; set; }

        public List<KeyValuePair<Guid, string>> ExternalServiceTrace
        {
            get
            {
                return _externalServiceTrace ?? (_externalServiceTrace = new List<KeyValuePair<Guid, string>>());
            }
            set
            {
                _externalServiceTrace = value;
            }
        }

        public long TransactionObjectId { get; set; }

        public bool IsInTestContext { get; set; }

        public bool AutoRollback { get; set; }

        public bool BypassWorkflowOperation { get; set; }

        public long DatabaseOperationCount { get; set; }

        public double DatabaseOperationsTotal { get; set; }

        public int HostRequestLength { get; set; }

        public int HostResponseLength { get; set; }

        public int OutboundOperationsTotal { get; set; }

        internal Dictionary<string, Dictionary<string, object>> Cache { get; set; }

        public List<object> SessionInitilizedConnections { get; set; }

        internal OperationActionContext OperationActionContext { get; set; }

        internal HostSyncronizationContext HostSyncronizationContext { get; set; }

        public string ChannelSessionId { get; set; }

        public string ServiceInterface { get; set; }

        public string OperationName { get; set; }

        public string OperationKey
        {
            get
            {
                if (string.IsNullOrEmpty(ServiceName) || string.IsNullOrEmpty(OperationName))
                {
                    return string.Empty;
                }
                return string.Format("{0}.{1}", ServiceName, OperationName);
            }
        }

        //public CRUDTypes OperationCrudType { get; set; }

        public string ServiceName
        {
            get
            {
                if (ServiceInterface == null)
                {
                    return string.Empty;
                }
                if (!ServiceInterface.StartsWith("I"))
                {
                    return ServiceInterface;
                }
                return ServiceInterface.Substring(1);
            }
        }

        public int CommitTime { get; set; }

        public string ClientIp { get; set; }

        public string CallerServerIp { get; set; }

        public string AccessToken { get; set; }

        public long QueueTicketId { get; set; }

        public int RaiseEventCount { get; set; }

        //public WorkflowInfo ApprovedWorkflowInfo { get; set; }

        public bool VirtualAddressActive { get; set; }

        public string VirtualAddress { get; set; }

        public string CompanyInfo { get; set; }

        public bool IsReceiptMaskEnabled { get; set; }

        public object Clone()
        {
            return Clone(false);
        }

        public object Clone(bool includeStatistics)
        {
            RequestCallContext requestCallContext = new RequestCallContext
            {
                BranchCode = BranchCode,
                Channel = Channel,
                IntegrationServiceAddress = IntegrationServiceAddress,
                IntegrationSecondaryServiceAddress = IntegrationSecondaryServiceAddress,
                IntegrationServiceLogEnabled = IntegrationServiceLogEnabled,
                IntegrationServicePassword = IntegrationServicePassword,
                IntegrationServicePort = IntegrationServicePort,
                IntegrationServiceProtocol = IntegrationServiceProtocol,
                IntegrationServiceUserName = IntegrationServiceUserName,
                Language = Language,
                MainRequestObjectId = MainRequestObjectId,
                RequestHashCode = RequestHashCode,
                RequestObjectId = RequestObjectId,
                ScreenCode = ScreenCode,
                SessionId = SessionId,
                TerminalId = TerminalId,
                TransactionObjectId = TransactionObjectId,
                UnitCode = UnitCode,
                UserCode = UserCode,
                UserPassword = UserPassword,
                UserSessionId = UserSessionId,
                ChannelSessionId = ChannelSessionId,
                ClientIp = ClientIp,
                CallerServerIp = CallerServerIp,
                AccessToken = AccessToken,
                QueueTicketId = QueueTicketId,
                OperationName = OperationName,
                ServiceInterface = ServiceInterface,
                IsInTestContext = IsInTestContext,
                AutoRollback = AutoRollback,
                ApprovedWorkflowInfo = ApprovedWorkflowInfo,
                IsIntegrationServiceProtocol10 = IsIntegrationServiceProtocol10,
                IsIntegrationServiceProtocol11 = IsIntegrationServiceProtocol11,
                IsIntegrationServiceProtocol12 = IsIntegrationServiceProtocol12,
                OpenTimeout = OpenTimeout,
                OperationTimeout = OperationTimeout,
                Environment = Environment,
                ConnectionOpenTime = ConnectionOpenTime,
                BypassWorkflowOperation = BypassWorkflowOperation,
                VirtualAddressActive = VirtualAddressActive,
                VirtualAddress = VirtualAddress,
                IsReceiptMaskEnabled = IsReceiptMaskEnabled
            };
            if (IntegrationServiceAddresses != null)
            {
                requestCallContext.IntegrationServiceAddresses = new List<LDTOIntegrationServiceDetail>(IntegrationServiceAddresses);
            }
            if (!includeStatistics)
            {
                return requestCallContext;
            }
            requestCallContext.DatabaseOperationCount = DatabaseOperationCount;
            requestCallContext.DatabaseOperationsTotal = DatabaseOperationsTotal;
            requestCallContext.ExternalServiceTrace = ExternalServiceTrace.Select((KeyValuePair<Guid, string> item) => new KeyValuePair<Guid, string>(item.Key, item.Value)).ToList();
            requestCallContext.HasHostOperationCall = HasHostOperationCall;
            requestCallContext.HostOperationCount = HostOperationCount;
            requestCallContext.HostOperationsTotal = HostOperationsTotal;
            requestCallContext.HostRequestLength = HostRequestLength;
            requestCallContext.HostResponseLength = HostResponseLength;
            requestCallContext.SessionInitilizedConnections = ((SessionInitilizedConnections != null) ? SessionInitilizedConnections.ToList() : null);
            requestCallContext.OperationActionContext = ((OperationActionContext == null) ? null : ((OperationActionContext)OperationActionContext.Clone()));
            requestCallContext.HostSyncronizationContext = ((HostSyncronizationContext == null) ? null : ((HostSyncronizationContext)HostSyncronizationContext.Clone()));
            requestCallContext.OutboundOperationsTotal = OutboundOperationsTotal;
            requestCallContext.CommitTime = CommitTime;
            requestCallContext.RaiseEventCount = RaiseEventCount;
            requestCallContext.Environment = Environment;
            requestCallContext.ConnectionOpenTime = ConnectionOpenTime;
            return requestCallContext;
        }
    }

}
