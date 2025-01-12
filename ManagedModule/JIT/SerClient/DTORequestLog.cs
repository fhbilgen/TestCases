using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [Serializable]
    [DataContract]
    public class DTORequestLog : BaseDataTransferObject, IDataTransferObject
    {
        private long _id;

        private long _vfaLogControlId;

        private string _mainrequest;

        private string _tbmsfFeeResponse;

        private string _tbmsfFeesResponse;

        private string _vfaFeeResponse;

        private string _vfaFeesResponse;

        private TbmsfVfaMatchType _matchType;

        private TbmsfVfaMatchType _matchFees;

        private long _tbmsfRequestId;

        private string _vfaPriceRequest;

        private string _vfaPriceResponse;

        private TbmsfFeeControl _tbmsffeecontrol;

        private IsSuccessful _vfaIsSuccess;

        private IsSuccessful _tbmsfIsSuccess;

        private string _customer;

        private string _account;

        private string _transactioncode;

        private decimal _tbmsftotalamount;

        private decimal _tbmsftaxamount;

        private decimal _tbmsffeeamount;

        private decimal _tbmsfcomissionamount;

        private decimal _vfatotalamount;

        private decimal _vfataxamount;

        private decimal _vfafeeamount;

        private decimal _vfacomissionamount;

        private string _tbmsfException;

        private string _vfaException;

        private decimal _entegrationduration;

        private decimal _vfaduration;

        private string _ipAdress;

        private string _transactiondetailcode;

        private TbmsfVfaMatchType _feeobjectmatch;

        private TbmsfVfaMatchType _feesobjectmatch;

        private string _feeDifferencies;

        private string _feesDifferencies;

        private string _masterfeesource;

        private NoFeeTypes _nofeetype;

        private string _tbmsffeesource;

        private string _vfafeesource;

        private string _exactdiff;

        private string _exactdifffees;

        private string _productcode;

        private string _campaigncode;

        private string _sahiplik;

        private string _dovizcinsi;

        private string _sorgumod;

        private string _hatamesaj;

        private string _hataaciklama;

        [ColumnName("VfaLogControlId")]
        [Required(true)]
        [Range(typeof(long), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public long VfaLogControlId
        {
            get
            {
                return _vfaLogControlId;
            }
            set
            {
                if (_vfaLogControlId != value)
                {
                    _vfaLogControlId = value;
                    OnPropertyChanged("VfaLogControlId");
                }
            }
        }

        [ColumnName("HataAciklama")]
        [Caption("HataAciklama")]
        [DataMember(EmitDefaultValue = false)]
        public string HataAciklama
        {
            get
            {
                return _hataaciklama;
            }
            set
            {
                if (_hataaciklama != value)
                {
                    _hataaciklama = value;
                    OnPropertyChanged("HataAciklama");
                }
            }
        }

        [ColumnName("HataMesaj")]
        [Caption("HataMesaj")]
        [DataMember(EmitDefaultValue = false)]
        public string HataMesaj
        {
            get
            {
                return _hatamesaj;
            }
            set
            {
                if (_hatamesaj != value)
                {
                    _hatamesaj = value;
                    OnPropertyChanged("HataMesaj");
                }
            }
        }

        [ColumnName("SorguMod")]
        [Caption("SorguMod")]
        [DataMember(EmitDefaultValue = false)]
        public string SorguMod
        {
            get
            {
                return _sorgumod;
            }
            set
            {
                if (_sorgumod != value)
                {
                    _sorgumod = value;
                    OnPropertyChanged("SorguMod");
                }
            }
        }

        [ColumnName("DovizCinsi")]
        [Caption("DovizCinsi")]
        [DataMember(EmitDefaultValue = false)]
        public string DovizCinsi
        {
            get
            {
                return _dovizcinsi;
            }
            set
            {
                if (_dovizcinsi != value)
                {
                    _dovizcinsi = value;
                    OnPropertyChanged("DovizCinsi");
                }
            }
        }

        [ColumnName("Sahiplik")]
        [Caption("Sahiplik")]
        [DataMember(EmitDefaultValue = false)]
        public string Sahiplik
        {
            get
            {
                return _sahiplik;
            }
            set
            {
                if (_sahiplik != value)
                {
                    _sahiplik = value;
                    OnPropertyChanged("Sahiplik");
                }
            }
        }

        [ColumnName("CAMPAIGNCODE")]
        [Caption("CampaignCode")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string CampaignCode
        {
            get
            {
                return _campaigncode;
            }
            set
            {
                if (_campaigncode != value)
                {
                    _campaigncode = value;
                    OnPropertyChanged("CampaignCode");
                }
            }
        }

        [ColumnName("PRODUCTCODE")]
        [Caption("ProductCode")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string ProductCode
        {
            get
            {
                return _productcode;
            }
            set
            {
                if (_productcode != value)
                {
                    _productcode = value;
                    OnPropertyChanged("ProductCode");
                }
            }
        }

        [ColumnName("EXACTDIFF")]
        [Caption("ExactDiff")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string ExactDiff
        {
            get
            {
                return _exactdiff;
            }
            set
            {
                if (_exactdiff != value)
                {
                    _exactdiff = value;
                    OnPropertyChanged("ExactDiff");
                }
            }
        }

        [ColumnName("EXACTDIFFFEES")]
        [Caption("ExactDifffees")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string ExactDifffees
        {
            get
            {
                return _exactdifffees;
            }
            set
            {
                if (_exactdifffees != value)
                {
                    _exactdifffees = value;
                    OnPropertyChanged("ExactDifffees");
                }
            }
        }

        [ColumnName("VFAFEESOURCE")]
        [Caption("VfaFeeSource")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string VfaFeeSource
        {
            get
            {
                return _vfafeesource;
            }
            set
            {
                if (_vfafeesource != value)
                {
                    _vfafeesource = value;
                    OnPropertyChanged("VfaFeeSource");
                }
            }
        }

        [ColumnName("TBMSFFEESOURCE")]
        [Caption("TbmsfFeeSource")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string TbmsfFeeSource
        {
            get
            {
                return _tbmsffeesource;
            }
            set
            {
                if (_tbmsffeesource != value)
                {
                    _tbmsffeesource = value;
                    OnPropertyChanged("TbmsfFeeSource");
                }
            }
        }

        [ColumnName("NoFeeType")]
        [Range(typeof(NoFeeTypes), Minimum = 0, Maximum = 0)]
        [DataMember(Name = "NoFeeCode", EmitDefaultValue = false)]
        public NoFeeTypes NoFeeType
        {
            get
            {
                return _nofeetype;
            }
            set
            {
                if (_nofeetype != value)
                {
                    _nofeetype = value;
                    OnPropertyChanged("NoFeeType");
                }
            }
        }

        [ColumnName("MASTERFEESOURCE")]
        [Caption("MasterFeeSource")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string MasterFeeSource
        {
            get
            {
                return _masterfeesource;
            }
            set
            {
                if (_masterfeesource != value)
                {
                    _masterfeesource = value;
                    OnPropertyChanged("MasterFeeSource");
                }
            }
        }

        [ColumnName("FEEDIFFERENCIES")]
        [Caption("FeeDifferencies")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string FeeDifferencies
        {
            get
            {
                return _feeDifferencies;
            }
            set
            {
                if (_feeDifferencies != value)
                {
                    _feeDifferencies = value;
                    OnPropertyChanged("FeeDifferencies");
                }
            }
        }

        [ColumnName("FEESDIFFERENCIES")]
        [Caption("FeesDifferencies")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string FeesDifferencies
        {
            get
            {
                return _feesDifferencies;
            }
            set
            {
                if (_feesDifferencies != value)
                {
                    _feesDifferencies = value;
                    OnPropertyChanged("FeesDifferencies");
                }
            }
        }

        [ColumnName("FEEOBJECTMATCH")]
        [Range(typeof(TbmsfVfaMatchType), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public TbmsfVfaMatchType FeeObjectMatch
        {
            get
            {
                return _feeobjectmatch;
            }
            set
            {
                if (_feeobjectmatch != value)
                {
                    _feeobjectmatch = value;
                    OnPropertyChanged("FeeObjectMatch");
                }
            }
        }

        [ColumnName("FEESOBJECTMATCH")]
        [Range(typeof(TbmsfVfaMatchType), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public TbmsfVfaMatchType FeesObjectMatch
        {
            get
            {
                return _feesobjectmatch;
            }
            set
            {
                if (_feesobjectmatch != value)
                {
                    _feesobjectmatch = value;
                    OnPropertyChanged("FeesObjectMatch");
                }
            }
        }

        [ColumnName("TRANSACTIONDETAILCODE")]
        [Caption("TransactionDetailCode")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string TransactionDetailCode
        {
            get
            {
                return _transactiondetailcode;
            }
            set
            {
                if (_transactiondetailcode != value)
                {
                    _transactiondetailcode = value;
                    OnPropertyChanged("TransactionDetailCode");
                }
            }
        }

        [ColumnName("IPADRESS")]
        [Caption("IpAdress")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string IpAdress
        {
            get
            {
                return _ipAdress;
            }
            set
            {
                if (_ipAdress != value)
                {
                    _ipAdress = value;
                    OnPropertyChanged("IpAdress");
                }
            }
        }

        [ColumnName("VFADURATION")]
        [Caption("VfaDuration")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal VfaDuration
        {
            get
            {
                return _vfaduration;
            }
            set
            {
                if (_vfaduration != value)
                {
                    _vfaduration = value;
                    OnPropertyChanged("VfaDuration");
                }
            }
        }

        [ColumnName("ENTEGRATIONDURATION")]
        [Caption("EntegrationDuration")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal EntegrationDuration
        {
            get
            {
                return _entegrationduration;
            }
            set
            {
                if (_entegrationduration != value)
                {
                    _entegrationduration = value;
                    OnPropertyChanged("EntegrationDuration");
                }
            }
        }

        [ColumnName("VFAEXCEPTION")]
        [Caption("VfaException")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string VfaException
        {
            get
            {
                return _vfaException;
            }
            set
            {
                if (_vfaException != value)
                {
                    _vfaException = value;
                    OnPropertyChanged("VfaException");
                }
            }
        }

        [ColumnName("TBMSFEXCEPTION")]
        [Caption("TbmsfException")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string TbmsfException
        {
            get
            {
                return _tbmsfException;
            }
            set
            {
                if (_tbmsfException != value)
                {
                    _tbmsfException = value;
                    OnPropertyChanged("TbmsfException");
                }
            }
        }

        [ColumnName("VFACOMISSIONAMOUNT")]
        [Caption("VfaComissionAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal VfaComissionAmount
        {
            get
            {
                return _vfacomissionamount;
            }
            set
            {
                if (_vfacomissionamount != value)
                {
                    _vfacomissionamount = value;
                    OnPropertyChanged("VfaComissionAmount");
                }
            }
        }

        [ColumnName("VFAFEEAMOUNT")]
        [Caption("VfaFeeAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal VfaFeeAmount
        {
            get
            {
                return _vfafeeamount;
            }
            set
            {
                if (_vfafeeamount != value)
                {
                    _vfafeeamount = value;
                    OnPropertyChanged("VfaFeeAmount");
                }
            }
        }

        [ColumnName("VFATAXAMOUNT")]
        [Caption("VfaTaxAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal VfaTaxAmount
        {
            get
            {
                return _vfataxamount;
            }
            set
            {
                if (_vfataxamount != value)
                {
                    _vfataxamount = value;
                    OnPropertyChanged("VfaTaxAmount");
                }
            }
        }

        [ColumnName("VFATOTALAMOUNT")]
        [Caption("VfaTotalAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal VfaTotalAmount
        {
            get
            {
                return _vfatotalamount;
            }
            set
            {
                if (_vfatotalamount != value)
                {
                    _vfatotalamount = value;
                    OnPropertyChanged("VfaTotalAmount");
                }
            }
        }

        [ColumnName("TBMSFCOMISSIONAMOUNT")]
        [Caption("TbmsfComissionAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal TbmsfComissionAmount
        {
            get
            {
                return _tbmsfcomissionamount;
            }
            set
            {
                if (_tbmsfcomissionamount != value)
                {
                    _tbmsfcomissionamount = value;
                    OnPropertyChanged("TbmsfComissionAmount");
                }
            }
        }

        [ColumnName("TBMSFFEEAMOUNT")]
        [Caption("TbmsfFeeAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal TbmsfFeeAmount
        {
            get
            {
                return _tbmsffeeamount;
            }
            set
            {
                if (_tbmsffeeamount != value)
                {
                    _tbmsffeeamount = value;
                    OnPropertyChanged("TbmsfFeeAmount");
                }
            }
        }

        [ColumnName("TBMSFTAXAMOUNT")]
        [Caption("TbmsfTaxAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal TbmsfTaxAmount
        {
            get
            {
                return _tbmsftaxamount;
            }
            set
            {
                if (_tbmsftaxamount != value)
                {
                    _tbmsftaxamount = value;
                    OnPropertyChanged("TbmsfTaxAmount");
                }
            }
        }

        [ColumnName("TBMSFTOTALAMOUNT")]
        [Caption("TbmsfTotalAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal TbmsfTotalAmount
        {
            get
            {
                return _tbmsftotalamount;
            }
            set
            {
                if (_tbmsftotalamount != value)
                {
                    _tbmsftotalamount = value;
                    OnPropertyChanged("TbmsfTotalAmount");
                }
            }
        }

        [ColumnName("TRANSACTIONCODE")]
        [Caption("TransactionCode")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string TransactionCode
        {
            get
            {
                return _transactioncode;
            }
            set
            {
                if (_transactioncode != value)
                {
                    _transactioncode = value;
                    OnPropertyChanged("TransactionCode");
                }
            }
        }

        [ColumnName("ACCOUNT")]
        [Caption("Account")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(Name = "AccountNumber", EmitDefaultValue = false)]
        public string Account
        {
            get
            {
                return _account;
            }
            set
            {
                if (_account != value)
                {
                    _account = value;
                    OnPropertyChanged("Account");
                }
            }
        }

        [ColumnName("CUSTOMER")]
        [Caption("Customer")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(Name = "CustomerNumber", EmitDefaultValue = false)]
        public string Customer
        {
            get
            {
                return _customer;
            }
            set
            {
                if (_customer != value)
                {
                    _customer = value;
                    OnPropertyChanged("Customer");
                }
            }
        }

        [ColumnName("TBMSFISSUCCESS")]
        [Range(typeof(TbmsfFeeControl), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public IsSuccessful TbmsfIsSuccess
        {
            get
            {
                return _tbmsfIsSuccess;
            }
            set
            {
                if (_tbmsfIsSuccess != value)
                {
                    _tbmsfIsSuccess = value;
                    OnPropertyChanged("TbmsfIsSuccess");
                }
            }
        }

        [ColumnName("VFAISSUCCESS")]
        [Range(typeof(TbmsfFeeControl), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public IsSuccessful VfaIsSuccess
        {
            get
            {
                return _vfaIsSuccess;
            }
            set
            {
                if (_vfaIsSuccess != value)
                {
                    _vfaIsSuccess = value;
                    OnPropertyChanged("VfaIsSuccess");
                }
            }
        }

        [ColumnName("TBMSFFEECONTROL")]
        [Range(typeof(TbmsfFeeControl), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public TbmsfFeeControl TbmsfFeeControl
        {
            get
            {
                return _tbmsffeecontrol;
            }
            set
            {
                if (_tbmsffeecontrol != value)
                {
                    _tbmsffeecontrol = value;
                    OnPropertyChanged("TbmsfFeeControl");
                }
            }
        }

        [ColumnName("VFAPRICERESPONSE")]
        [Caption("VFAPRICERESPONSE")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string VfaPriceResponse
        {
            get
            {
                return _vfaPriceResponse;
            }
            set
            {
                if (_vfaPriceResponse != value)
                {
                    _vfaPriceResponse = value;
                    OnPropertyChanged("VfaPriceResponse");
                }
            }
        }

        [ColumnName("VFAPRICEREQUEST")]
        [Caption("VFAPRICEREQUEST")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string VfaPriceRequest
        {
            get
            {
                return _vfaPriceRequest;
            }
            set
            {
                if (_vfaPriceRequest != value)
                {
                    _vfaPriceRequest = value;
                    OnPropertyChanged("VfaPriceRequest");
                }
            }
        }

        [ColumnName("TBMSFREQUESTID")]
        [Required(true)]
        [Range(typeof(long), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public long TbmsfRequestId
        {
            get
            {
                return _tbmsfRequestId;
            }
            set
            {
                if (_tbmsfRequestId != value)
                {
                    _tbmsfRequestId = value;
                    OnPropertyChanged("TbmsfRequestId");
                }
            }
        }

        [ColumnName("MATCHTYPE")]
        [Range(typeof(TbmsfVfaMatchType), Minimum = 0, Maximum = 0)]
        [DataMember(Name = "Match", EmitDefaultValue = false)]
        public TbmsfVfaMatchType MatchType
        {
            get
            {
                return _matchType;
            }
            set
            {
                if (_matchType != value)
                {
                    _matchType = value;
                    OnPropertyChanged("MatchType");
                }
            }
        }

        [ColumnName("MATCHFEES")]
        [Range(typeof(TbmsfVfaMatchType), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public TbmsfVfaMatchType MatchFees
        {
            get
            {
                return _matchFees;
            }
            set
            {
                if (_matchFees != value)
                {
                    _matchFees = value;
                    OnPropertyChanged("MATCHFEES");
                }
            }
        }

        [ColumnName("VFAFEERESPONSE")]
        [Caption("VFAFEERESPONSE")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string VfaFeeResponse
        {
            get
            {
                return _vfaFeeResponse;
            }
            set
            {
                if (_vfaFeeResponse != value)
                {
                    _vfaFeeResponse = value;
                    OnPropertyChanged("VfaFeeResponse");
                }
            }
        }

        [ColumnName("VFAFEESRESPONSE")]
        [Caption("VFAFEESRESPONSE")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string VfaFeesResponse
        {
            get
            {
                return _vfaFeesResponse;
            }
            set
            {
                if (_vfaFeesResponse != value)
                {
                    _vfaFeesResponse = value;
                    OnPropertyChanged("VfaFeesResponse");
                }
            }
        }

        [ColumnName("TBMSFFEERESPONSE")]
        [Caption("TBMSFFEERESPONSE")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string TbmsfFeeResponse
        {
            get
            {
                return _tbmsfFeeResponse;
            }
            set
            {
                if (_tbmsfFeeResponse != value)
                {
                    _tbmsfFeeResponse = value;
                    OnPropertyChanged("TbmsfFeeResponse");
                }
            }
        }

        [ColumnName("TBMSFFEESRESPONSE")]
        [Caption("TBMSFFEESRESPONSE")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string TbmsfFeesResponse
        {
            get
            {
                return _tbmsfFeesResponse;
            }
            set
            {
                if (_tbmsfFeesResponse != value)
                {
                    _tbmsfFeesResponse = value;
                    OnPropertyChanged("TbmsfFeesResponse");
                }
            }
        }

        [ColumnName("MAINREQUEST")]
        [Caption("MAINREQUEST")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string MainRequest
        {
            get
            {
                return _mainrequest;
            }
            set
            {
                if (_mainrequest != value)
                {
                    _mainrequest = value;
                    OnPropertyChanged("MainRequest");
                }
            }
        }

        [ColumnName("ID")]
        [Required(true)]
        [Range(typeof(long), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public long ID
        {
            get
            {
                return _id;
            }
            set
            {
                if (_id != value)
                {
                    _id = value;
                    OnPropertyChanged("ID");
                }
            }
        }

        public new BaseDataTransferObject Copy()
        {
            DTORequestLog dTORequestLog = new DTORequestLog();
            dTORequestLog.ID = ID;
            dTORequestLog.MainRequest = MainRequest;
            dTORequestLog.TbmsfFeeResponse = TbmsfFeeResponse;
            dTORequestLog.TbmsfFeesResponse = TbmsfFeesResponse;
            dTORequestLog.VfaFeeResponse = VfaFeeResponse;
            dTORequestLog.VfaFeesResponse = VfaFeesResponse;
            dTORequestLog.MatchType = MatchType;
            dTORequestLog.MatchFees = MatchFees;
            dTORequestLog.TbmsfRequestId = TbmsfRequestId;
            dTORequestLog.VfaPriceRequest = VfaPriceRequest;
            dTORequestLog.VfaPriceResponse = VfaPriceResponse;
            dTORequestLog.TbmsfFeeControl = TbmsfFeeControl;
            dTORequestLog.VfaIsSuccess = VfaIsSuccess;
            dTORequestLog.TbmsfIsSuccess = TbmsfIsSuccess;
            dTORequestLog.Customer = Customer;
            dTORequestLog.Account = Account;
            dTORequestLog.TransactionCode = TransactionCode;
            dTORequestLog.TbmsfComissionAmount = TbmsfComissionAmount;
            dTORequestLog.TbmsfFeeAmount = TbmsfFeeAmount;
            dTORequestLog.TbmsfTaxAmount = TbmsfTaxAmount;
            dTORequestLog.TbmsfTotalAmount = TbmsfTotalAmount;
            dTORequestLog.VfaComissionAmount = VfaComissionAmount;
            dTORequestLog.VfaTotalAmount = VfaTotalAmount;
            dTORequestLog.VfaTaxAmount = VfaTaxAmount;
            dTORequestLog.VfaFeeAmount = VfaFeeAmount;
            dTORequestLog.TbmsfException = TbmsfException;
            dTORequestLog.VfaException = VfaException;
            dTORequestLog.VfaDuration = VfaDuration;
            dTORequestLog.EntegrationDuration = EntegrationDuration;
            dTORequestLog.IpAdress = IpAdress;
            dTORequestLog.TransactionDetailCode = TransactionDetailCode;
            dTORequestLog.FeeObjectMatch = FeeObjectMatch;
            dTORequestLog.FeesObjectMatch = FeesObjectMatch;
            dTORequestLog.FeeDifferencies = FeeDifferencies;
            dTORequestLog.FeesDifferencies = FeesDifferencies;
            dTORequestLog.MasterFeeSource = MasterFeeSource;
            dTORequestLog.NoFeeType = NoFeeType;
            dTORequestLog.TbmsfFeeSource = TbmsfFeeSource;
            dTORequestLog.VfaFeeSource = VfaFeeSource;
            dTORequestLog.ExactDiff = ExactDiff;
            dTORequestLog.ExactDifffees = ExactDifffees;
            dTORequestLog.ProductCode = ProductCode;
            dTORequestLog.CampaignCode = CampaignCode;
            dTORequestLog.Sahiplik = Sahiplik;
            dTORequestLog.SorguMod = SorguMod;
            dTORequestLog.DovizCinsi = DovizCinsi;
            dTORequestLog.HataMesaj = HataMesaj;
            dTORequestLog.HataAciklama = HataAciklama;
            dTORequestLog.VfaLogControlId = VfaLogControlId;
            dTORequestLog.FillBaseProperties(this);
            return dTORequestLog;
        }
    }

}
