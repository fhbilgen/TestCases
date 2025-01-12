using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Transactions;

namespace ManagedModule.JIT.SerClient
{
    public class Database
    {
        internal const string LOGGING_KEY = "DBPROXY";

        internal const string DEFAULT_DATASOURCE = "Main";

        internal const int NULL_COMMAND_TIMEOUT = -1;

        internal const long NULL_FETCH_SIZE = 0L;

        internal const int NULL_INITIAL_LOB_FETCH_SIZE = -2;

        private const string SP_CACHE_SELECTION_SP = "DAL_L_CACHEALL";

        private const string SP_EXECUTION_LIMIT_SP = "DAL_L_EXECUTIONLIMIT";

        private const string SP_ARCHIVE_PROJECTION = "DAL_L_ARCPROJBYSOURCE";

        private static readonly List<string> _prohibitedWords = new List<string>
    {
        "UPDATE ", "INSERT ", "DELETE ", "EXEC ", "EXECUTE ", "CREATE ", "DROP ", "ALTER ", "GRANT ", "REVOKE ",
        "TRUNCATE ", "RENAME ", "CALL ", "LOCK "
    };

        private static readonly bool _cacheSPResults = ConfigurationManager.Read("CacheSPResults", false);

        private static readonly bool _useConfig = ConfigurationManager.Read("DataAccessUseConfig", false);

        private readonly string _dataSource = string.Empty;

        private DataSourceInformation _dataSourceInformation;

        private int _commandTimeout = -1;

        private long _fetchSize;

        private int _initialLOBFetchSize = -2;

        private static readonly string _configConnectionString = ConfigurationManager.Read("ConnectionString", string.Empty);

        private static readonly string _configDataSourceName = ConfigurationManager.Read("DataSourceName", "Main");

        private static readonly bool _configSetSessionContext = ConfigurationManager.Read("SetSessionContextEnabled", true);

        private static readonly DataSourceProviderType _configDataSourceProviderType = (DataSourceProviderType)ConfigurationManager.Read("ProviderType", 1);

        internal const string DB_PROXY_DEFINITION_PARAMETER_KEY = "DALDBPROXYLIST";

        private const string DB_PROXY_ENDPOINT_ADDRESS_CONFIG_KEY = "DbProxyEndpointAddress";

        private IDBProxyService _proxyClient;

        private string _dbProxyEndpointAddress;

        private bool _alwaysUseProxy;

        private bool _byPassProxy;

        public BaseDatabase _database;

        private bool IsProxyApp
        {
            get
            {
                return string.IsNullOrWhiteSpace(_dbProxyEndpointAddress);
            }
        }

        private bool UseProxy
        {
            get
            {
                if (ByPassProxy)
                {
                    return false;
                }
                if (!AlwaysUseProxy)
                {
                    if (!IsProxyApp && !_dataSource.Equals("Main"))
                    {
                        return IsProxyEnabledForDataSource();
                    }
                    return false;
                }
                return true;
            }
        }

        internal bool ByPassProxy
        {
            get
            {
                return _byPassProxy;
            }
            set
            {
                _byPassProxy = value;
            }
        }

        internal IDBProxyService ProxyClient
        {
            get
            {
                return _proxyClient;
            }
        }

        public bool AlwaysUseProxy
        {
            get
            {
                return _alwaysUseProxy;
            }
            set
            {
                _alwaysUseProxy = value;
            }
        }

        public BaseDatabase DatabaseInstance
        {
            get
            {
                if (_database == null)
                {
                    Initialize();
                }
                return _database;
            }
        }

        public DataSourceProviderType DataSourceProviderType { get; private set; }

        internal Database WithCommandTimeout(int commandTimeout)
        {
            if (commandTimeout > -1)
            {
                _commandTimeout = commandTimeout;
            }
            return this;
        }

        internal Database WithFetchSize(long fetchSize)
        {
            if (fetchSize > 0)
            {
                _fetchSize = fetchSize;
            }
            return this;
        }

        internal Database WithInitialLOBFetchSize(int initialLOBFetchSize)
        {
            if (_initialLOBFetchSize > -2)
            {
                _initialLOBFetchSize = initialLOBFetchSize;
            }
            return this;
        }

        private static Dictionary<string, bool> GetDataSourceProxySettings()
        {
            try
            {
                return ParameterProvider.GetParameter("DALDBPROXYLIST").ToDictionary((DTOParameter p) => p.Detail1, (DTOParameter p) => p.Detail2.ToBoolean());
            }
            catch (Exception ex)
            {
                TraceController.TraceError(TraceEventCategories.None, "DBPROXY", ex.ToString());
                return new Dictionary<string, bool>();
            }
        }

        private void InitializeDbProxy()
        {
            _dbProxyEndpointAddress = ConfigurationManager.Read("DbProxyEndpointAddress", string.Empty);
            if (!IsProxyApp)
            {
                _proxyClient = new DBProxyClientFactory(_dbProxyEndpointAddress).GetDbProxyClient();
            }
        }

        private bool IsProxyEnabledForDataSource()
        {
            return ProxyUsageCacheManager.UseProxy(_dataSource).UseProxy;
        }

        protected T LogProxyExecutionTime<T>(Func<T> executor, string commandText)
        {
            double time;
            T result = Utils.MeasureTimeElapsed(executor, out time);
            if (TraceController.IsTraceActive)
            {
                TraceController.TraceInformation(TraceEventCategories.DBPROXY, CallerInformation.MainRequestObjectId, CallerInformation.UserCode, "{0}|{1}|{2}", "DBPROXY", commandText, (int)time);
            }
            return result;
        }

        protected ExecutionLimit GetExecutionLimit(string commandText)
        {
            if (commandText != "DAL_L_EXECUTIONLIMIT" && commandText != "APP_L_SCREENBYSCREENTYPE" && commandText != "APP_S_DATAGUARDDATETIME" && commandText != "PAR_L_PARAMETERBYGROUPCODE")
            {
                return DatabaseExecutionLimits.CheckStatusAndGetExecutionLimit(_dataSource, commandText);
            }
            return null;
        }

        protected TResult Execute<TResult>(Func<TResult> internalExecutor, Func<DbResultMessage<TResult>> proxyExecutor, DatabaseParameters parameters)
        {
            try
            {
                if (UseProxy)
                {
                    DbResultMessage<TResult> dbResultMessage = proxyExecutor();
                    if (parameters != null)
                    {
                        DatabaseParameters parameters2 = dbResultMessage.Parameters;
                        if (parameters2 != null)
                        {
                            for (int i = 0; i < parameters2.Count; i++)
                            {
                                parameters[i].Value = parameters2[i].Value;
                            }
                        }
                    }
                    return dbResultMessage.Result;
                }
                if (_database == null)
                {
                    Initialize();
                }
                return internalExecutor();
            }
            catch (DbException)
            {
                TraceController.TraceError(TraceEventCategories.D, "DBPROXY", string.Format("Database error, key: {0}", _dataSource));
                throw;
            }
        }

        public static void ReloadDataSourceInformation()
        {
            DataSourceInformationHelper.ReloadDataSourceInformation();
        }

        public Database()
            : this(string.Empty)
        {
        }

        public Database(string dataSource)
        {
            DataSourceProviderType = DataSourceProviderType.None;
            _dataSource = (dataSource.Equals(string.Empty) ? "Main" : dataSource);
            if (!string.IsNullOrEmpty(CallerInformation.ScreenCode) && CallerInformation.ScreenCode.Length == 10 && CallerInformation.ScreenCode[3] == 'L' && CallerInformationInitializer.OperationCrudType == CRUDTypes.Read && CallerInformationInitializer.Channel != Channels.AsynchronousOperation && _dataSource == "Main")
            {
                bool flag = false;
                try
                {
                    flag = ((!(Transaction.Current == null)) ? true : false);
                }
                catch (Exception)
                {
                    flag = true;
                }
                if (!flag)
                {
                    if (CallerInformation.UserCode == "VB34857" || CallerInformation.UserCode == "vb34857" || CallerInformation.UserCode == "vb27305" || CallerInformation.UserCode == "VB27305" || CallerInformation.UserCode == "VB29981" || CallerInformation.UserCode == "vb29981")
                    {
                        GenericCacheItem cachingCacheItemParametersDataGuard = getCachingCacheItemParametersDataGuard("DALDataGuardMainTimeDif");
                        if (cachingCacheItemParametersDataGuard != null)
                        {
                            Dictionary<string, double> groupCodeTimeMapping = cachingCacheItemParametersDataGuard.GroupCodeTimeMapping;
                            double? obj;
                            if (groupCodeTimeMapping == null)
                            {
                                obj = null;
                            }
                            else
                            {
                                Dictionary<string, double>.ValueCollection values = groupCodeTimeMapping.Values;
                                obj = ((values != null) ? new double?(values.FirstOrDefault()) : null);
                            }
                            double? num = obj;
                            if (num.HasValue && num >= 0.0)
                            {
                                GenericCacheItem cachingCacheItemDataGuard = getCachingCacheItemDataGuard();
                                bool value = false;
                                cachingCacheItemDataGuard.ScreenDataGuardMapping.TryGetValue(CallerInformation.ScreenCode, out value);
                                if (value)
                                {
                                    _dataSource = "DATAGUARD";
                                    ByPassProxy = true;
                                    DateTime dataGuardDateTime = GetDataGuardDateTime();
                                    if ((DateTime.Now - dataGuardDateTime).TotalSeconds > num)
                                    {
                                        _dataSource = "Main";
                                        ByPassProxy = false;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        GenericCacheItem cachingCacheItemDataGuard2 = getCachingCacheItemDataGuard();
                        bool value2 = false;
                        cachingCacheItemDataGuard2.ScreenDataGuardMapping.TryGetValue(CallerInformation.ScreenCode, out value2);
                        if (value2)
                        {
                            _dataSource = "DATAGUARD";
                            ByPassProxy = true;
                        }
                    }
                }
            }
            InitializeDbProxy();
        }

        private void Initialize()
        {
            object data = AppDomain.CurrentDomain.GetData("ManualDatabaseConnections");
            if (data != null)
            {
                DatasourceInfo value;
                if (!((Dictionary<string, DatasourceInfo>)data).TryGetValue(_dataSource, out value))
                {
                    throw new Exception(string.Format("DataSource = {0} is not defined in debugging database list", _dataSource));
                }
                DataSourceProviderType = (DataSourceProviderType)value.ProviderType;
                switch (DataSourceProviderType)
                {
                    case DataSourceProviderType.Oracle:
                        _database = new OracleDatabase(value.ConnectionString, _dataSource);
                        break;
                    case DataSourceProviderType.MSSql:
                        _database = new MSSqlDatabase(value.ConnectionString, _dataSource);
                        break;
                    case DataSourceProviderType.Sybase:
                        _database = new SybaseDatabase(value.ConnectionString, _dataSource);
                        break;
                    default:
                        throw new NotSupportedException(string.Format("Unsupproted DataBase. Type:{0}", Enum.GetName(typeof(DataSourceProviderType), DataSourceProviderType)));
                }
                DatabaseInstance.ExecutionLimitControlEnabled = true;
                DatabaseInstance.SetSessionContextEnabled = true;
            }
            else if (!_useConfig)
            {
                _dataSourceInformation = DataSourceInformationHelper.GetDataSourceInformation(_dataSource);
                DataSourceProviderType = _dataSourceInformation.DataSourceProvider;
                switch (DataSourceProviderType)
                {
                    case DataSourceProviderType.Oracle:
                        _database = new OracleDatabase(_dataSourceInformation);
                        break;
                    case DataSourceProviderType.MSSql:
                        _database = new MSSqlDatabase(_dataSourceInformation);
                        break;
                    case DataSourceProviderType.Sybase:
                        _database = new SybaseDatabase(_dataSourceInformation);
                        break;
                    default:
                        throw new NotSupportedException(string.Format("Unsupproted DataBase. Type:{0}", Enum.GetName(typeof(DataSourceProviderType), DataSourceProviderType)));
                }
                DatabaseInstance.ExecutionLimitControlEnabled = _dataSourceInformation.ExecutionLimitEnabled;
                DatabaseInstance.SetSessionContextEnabled = _dataSourceInformation.SessionContextEnabled;
            }
            else
            {
                switch (_configDataSourceProviderType)
                {
                    case DataSourceProviderType.Oracle:
                        _database = new OracleDatabase(_configConnectionString, _configDataSourceName)
                        {
                            SetSessionContextEnabled = _configSetSessionContext
                        };
                        break;
                    case DataSourceProviderType.MSSql:
                        _database = new MSSqlDatabase(_configConnectionString, _configDataSourceName)
                        {
                            SetSessionContextEnabled = _configSetSessionContext
                        };
                        break;
                    case DataSourceProviderType.Sybase:
                        _database = new SybaseDatabase(_configConnectionString, _configDataSourceName)
                        {
                            SetSessionContextEnabled = _configSetSessionContext
                        };
                        break;
                    default:
                        throw new NotSupportedException(string.Format("Unsupproted DataBase. Type:{0}", Enum.GetName(typeof(DataSourceProviderType), DataSourceProviderType)));
                }
            }
            _database.SetCommandTimeout(_commandTimeout);
            _database.SetFetchSize(_fetchSize);
            _database.SetInitialLOBFetchSize(_initialLOBFetchSize);
        }

        private static DataTable GetCachingMetadata()
        {
            Database database = new Database();
            DatabaseParameters databaseParameters = new DatabaseParameters();
            databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
            return database.ExecuteDataSet("DAL_L_CACHEALL", databaseParameters).Tables[0];
        }

        private DataTable GetCachingParameterDataForDataGuard(string groupCode)
        {
            DatabaseParameters databaseParameters = new DatabaseParameters();
            databaseParameters.AddInParameter("GROUPCODE", groupCode, DatabaseTypes.String);
            databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
            return DatabaseInstance.ExecuteDataSet("PAR_L_PARAMETERBYGROUPCODE", databaseParameters).Tables[0];
        }

        private DataTable GetCachingMetaDataForDataGuard()
        {
            DatabaseParameters databaseParameters = new DatabaseParameters();
            databaseParameters.AddInParameter("SCREENTYPE", 4, DatabaseTypes.Int32);
            databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
            return DatabaseInstance.ExecuteDataSet("APP_L_SCREENBYSCREENTYPE", databaseParameters).Tables[0];
        }

        private DateTime GetDataGuardDateTime()
        {
            DatabaseParameters databaseParameters = new DatabaseParameters();
            databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
            DataTable dataTable = DatabaseInstance.ExecuteDataSet("APP_S_DATAGUARDDATETIME", databaseParameters).Tables[0];
            if (dataTable.Rows[0]["DB_TIME"] != DBNull.Value)
            {
                return Convert.ToDateTime(dataTable.Rows[0]["DB_TIME"]);
            }
            return DateTime.MinValue;
        }

        private static DataTable getArchiveProjectionSPsToBeCached(string dataSource)
        {
            Database database = new Database();
            DatabaseParameters databaseParameters = new DatabaseParameters();
            databaseParameters.AddInParameter("DATASOURCE", dataSource, DatabaseTypes.String);
            databaseParameters.AddOutParameter("RC", null, DatabaseTypes.RefCursor);
            return database.ExecuteDataSet("DAL_L_ARCPROJBYSOURCE", databaseParameters).Tables[0];
        }

        private static bool IsProhibitedWordsInTheText(string text)
        {
            string upperText = text.ToUpper(new CultureInfo("EN"));
            return _prohibitedWords.Any((string word) => upperText.IndexOf(word, StringComparison.Ordinal) > -1);
        }

        private CachingCacheItem getCachingCacheItem(string dataSource)
        {
            CachingCacheItem cachingCacheItem = BaseCacheManager<CachingCacheItem>.Get(_dataSource);
            if (cachingCacheItem == null)
            {
                DataTable cachingMetadata = GetCachingMetadata();
                CachingCacheManager.AddMetadata(_dataSource, cachingMetadata);
                cachingCacheItem = BaseCacheManager<CachingCacheItem>.Get(_dataSource);
            }
            return cachingCacheItem;
        }

        private string createSPResultCacheKey(string storedProcedureName, DatabaseParameters parameters)
        {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append(_dataSource);
            stringBuilder.Append(":");
            stringBuilder.Append(storedProcedureName);
            foreach (DatabaseParameter parameter in parameters)
            {
                stringBuilder.Append(":");
                stringBuilder.Append(parameter.Value.ToString());
            }
            return stringBuilder.ToString();
        }

        private GenericCacheItem getCachingCacheItemDataGuard()
        {
            GenericCacheItem genericCacheItem = BaseCacheManager<GenericCacheItem>.Get("DATAGUARD");
            if (genericCacheItem == null)
            {
                DataTable cachingMetaDataForDataGuard = GetCachingMetaDataForDataGuard();
                DataGuardCacheManager.AddItemScreenCode("DATAGUARD", cachingMetaDataForDataGuard);
                genericCacheItem = BaseCacheManager<GenericCacheItem>.Get("DATAGUARD");
            }
            return genericCacheItem;
        }

        private GenericCacheItem getCachingCacheItemParametersDataGuard(string groupCode)
        {
            GenericCacheItem genericCacheItem = BaseCacheManager<GenericCacheItem>.Get("PARAMETER_DALDataGuardMainTimeDif");
            if (genericCacheItem == null)
            {
                DataTable cachingParameterDataForDataGuard = GetCachingParameterDataForDataGuard(groupCode);
                DataGuardCacheManager.AddItemParam("PARAMETER_DALDataGuardMainTimeDif", cachingParameterDataForDataGuard);
                genericCacheItem = BaseCacheManager<GenericCacheItem>.Get("PARAMETER_DALDataGuardMainTimeDif");
            }
            return genericCacheItem;
        }

        private Dictionary<string, DTOArchiveProjection> getArchiveProjectionSPs(string dataSource)
        {
            ArchiveProjectionCacheItem archiveProjectionCacheItem = BaseCacheManager<ArchiveProjectionCacheItem>.Get(_dataSource);
            if (archiveProjectionCacheItem == null)
            {
                DataTable archiveProjectionSPsToBeCached = getArchiveProjectionSPsToBeCached(_dataSource);
                ArchiveProjectionCacheManager.AddMetadata(_dataSource, archiveProjectionSPsToBeCached);
                archiveProjectionCacheItem = BaseCacheManager<ArchiveProjectionCacheItem>.Get(_dataSource);
            }
            return archiveProjectionCacheItem.SPList;
        }

        public void DisposeDBInstance()
        {
            _database = null;
        }

        public DataSet ExecuteDataSet(string storedProcedureName, DatabaseParameters parameters)
        {
            return Execute(() => ExecuteDataSetInternal(storedProcedureName, parameters), () => ExecuteDataSetProxy(storedProcedureName, parameters), parameters);
        }

        [Obsolete("Bu method artık desteklenmemektedir. Yerine ExecuteDataSet method'u kullanılmalıdır.")]
        public DataSet ExecuteDataSetParameterized(string text, DatabaseParameters parameters)
        {
            return Execute(() => ExecuteDataSetParameterizedInternal(text, parameters), () => ExecuteDataSetParameterizedProxy(text, parameters), parameters);
        }

        public int ExecuteNonQuery(string storedProcedureName, DatabaseParameters parameters)
        {
            return Execute(() => ExecuteNonQueryInternal(storedProcedureName, parameters), () => ExecuteNonQueryProxy(storedProcedureName, parameters), parameters);
        }

        public object ExecuteScalar(string storedProcedureName, DatabaseParameters parameters)
        {
            return Execute(() => ExecuteScalarInternal(storedProcedureName, parameters), () => ExecuteScalarProxy(storedProcedureName, parameters), parameters);
        }

        public object ExecuteScalarParameterized(string text, DatabaseParameters parameters)
        {
            return Execute(() => ExecuteScalarParameterizedInternal(text, parameters), () => ExecuteScalarParameterizedProxy(text, parameters), parameters);
        }

        public Database WithExecutionLimit(ExecutionLimit executionLimit)
        {
            DatabaseInstance.ExecutionLimit = executionLimit;
            return this;
        }

        private DataSet ExecuteDataSetInternal(string storedProcedureName, DatabaseParameters parameters)
        {
            DataSet dataSet = null;
            if (_cacheSPResults && storedProcedureName != "DAL_L_CACHEALL" && storedProcedureName != "DAL_L_EXECUTIONLIMIT")
            {
                CachingCacheItem cachingCacheItem = getCachingCacheItem(_dataSource);
                if (cachingCacheItem.SPList.ContainsKey(storedProcedureName))
                {
                    string key = createSPResultCacheKey(storedProcedureName, parameters);
                    SpResultCacheItem spResultCacheItem = BaseCacheManager<SpResultCacheItem>.Get(key);
                    if (spResultCacheItem == null)
                    {
                        dataSet = DatabaseInstance.ExecuteDataSet(storedProcedureName, parameters);
                        SpResultCacheManager.AddSpResult(key, dataSet, cachingCacheItem.SPList[storedProcedureName]);
                    }
                    else
                    {
                        dataSet = spResultCacheItem.Value;
                    }
                }
                else
                {
                    dataSet = DatabaseInstance.ExecuteDataSet(storedProcedureName, parameters);
                }
            }
            else
            {
                dataSet = DatabaseInstance.ExecuteDataSet(storedProcedureName, parameters);
                CallerInformationInitializer.DatabaseOperationCount++;
            }
            DTOArchiveProjection value;
            if (_dataSource.Equals("Main") && DatabaseInstance is OracleDatabase && !storedProcedureName.StartsWith("DAL_") && getArchiveProjectionSPs(_dataSource).TryGetValue(storedProcedureName, out value))
            {
                if (value.ProjectionType == ProjectionTypes.Unmixed && dataSet.Tables[0].Rows.Count < 1)
                {
                    dataSet = new Database("ARC").ExecuteDataSet(storedProcedureName, parameters);
                }
                else if (value.ProjectionType == ProjectionTypes.Mixed)
                {
                    DataSet dataSet2 = new Database("ARC").ExecuteDataSet(storedProcedureName, parameters);
                    try
                    {
                        dataSet.Merge(dataSet2, false, MissingSchemaAction.Add);
                        return dataSet;
                    }
                    catch (ConstraintException ex)
                    {
                        throw new BaseException("Table constraint was violated.", new string[1] { ex.Message });
                    }
                    catch (Exception ex2)
                    {
                        throw new BaseException("Could not merge data tables.", new string[1] { ex2.Message });
                    }
                }
            }
            return dataSet;
        }

        private DataSet ExecuteDataSetParameterizedInternal(string text, DatabaseParameters parameters)
        {
            if (IsProhibitedWordsInTheText(text))
            {
                throw new BaseException(ExceptionMessages.DataAccessLayerSQLHasProhibitedWords);
            }
            DataSet result = DatabaseInstance.ExecuteDataSetParameterized(text, parameters);
            CallerInformationInitializer.DatabaseOperationCount++;
            return result;
        }

        private int ExecuteNonQueryInternal(string storedProcedureName, DatabaseParameters parameters)
        {
            int result = DatabaseInstance.ExecuteNonQuery(storedProcedureName, parameters);
            CallerInformationInitializer.DatabaseOperationCount++;
            return result;
        }

        private object ExecuteScalarInternal(string storedProcedureName, DatabaseParameters parameters)
        {
            object result = DatabaseInstance.ExecuteScalar(storedProcedureName, parameters);
            CallerInformationInitializer.DatabaseOperationCount++;
            return result;
        }

        private object ExecuteScalarParameterizedInternal(string text, DatabaseParameters parameters)
        {
            if (IsProhibitedWordsInTheText(text))
            {
                throw new BaseException(ExceptionMessages.DataAccessLayerSQLHasProhibitedWords);
            }
            object result = DatabaseInstance.ExecuteScalarParameterized(text, parameters);
            CallerInformationInitializer.DatabaseOperationCount++;
            return result;
        }

        private DbResultMessage<object> ExecuteScalarParameterizedProxy(string commandText, DatabaseParameters parameters)
        {
            return LogProxyExecutionTime(() => ProxyClient.ExecuteScalarParameterized(new DbCommandMessage
            {
                DataSourceName = _dataSource,
                CommandText = commandText,
                Parameters = parameters,
                ExecutionLimit = GetExecutionLimit(commandText)
            }), commandText).Result;
        }

        private DbResultMessage<object> ExecuteScalarProxy(string commandText, DatabaseParameters parameters)
        {
            return LogProxyExecutionTime(() => ProxyClient.ExecuteScalar(new DbCommandMessage
            {
                DataSourceName = _dataSource,
                CommandText = commandText,
                Parameters = parameters,
                ExecutionLimit = GetExecutionLimit(commandText)
            }), commandText).Result;
        }

        private DbResultMessage<int> ExecuteNonQueryProxy(string commandText, DatabaseParameters parameters)
        {
            return LogProxyExecutionTime(() => ProxyClient.ExecuteNonQuery(new DbCommandMessage
            {
                DataSourceName = _dataSource,
                CommandText = commandText,
                Parameters = parameters,
                ExecutionLimit = GetExecutionLimit(commandText)
            }), commandText).Result;
        }

        private DbResultMessage<DataSet> ExecuteDataSetProxy(string commandText, DatabaseParameters parameters)
        {
            return LogProxyExecutionTime(() => ProxyClient.ExecuteDataSet(new DbCommandMessage
            {
                DataSourceName = _dataSource,
                CommandText = commandText,
                Parameters = parameters,
                ExecutionLimit = GetExecutionLimit(commandText)
            }), commandText).Result;
        }

        private DbResultMessage<DataSet> ExecuteDataSetParameterizedProxy(string commandText, DatabaseParameters parameters)
        {
            return LogProxyExecutionTime(() => ProxyClient.ExecuteDataSetParameterized(new DbCommandMessage
            {
                DataSourceName = _dataSource,
                CommandText = commandText,
                Parameters = parameters,
                ExecutionLimit = GetExecutionLimit(commandText)
            }), commandText).Result;
        }
    }

}
