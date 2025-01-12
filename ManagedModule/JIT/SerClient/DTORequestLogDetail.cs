using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Security.AccessControl;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [Serializable]
    [DataContract]
    public class DTORequestLogDetail : BaseDataTransferObject, IDataTransferObject
    {
        private long _id;
        private long _vfalogcontrolid;

        private string _chargecode;

        private FeeSourceType _feesource;

        private decimal _feeamount;

        private decimal _taxamount;

        private decimal _totalamount;

        private decimal _standartamount;

        private decimal _comissionamount;

        private FeeLevelTypes _feeleveltype;

        private string _currency;

        private string _privilegeid;

        private decimal _bankamount;

        [ColumnName("BANKAMOUNT")]
        [Caption("BankAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal BankAmount
        {
            get
            {
                return _bankamount;
            }
            set
            {
                if (_bankamount != value)
                {
                    _bankamount = value;
                    OnPropertyChanged("BankAmount");
                }
            }
        }

        [ColumnName("PRIVILEGEID")]
        [Caption("PrivilegeId")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string PrivilegeId
        {
            get
            {
                return _privilegeid;
            }
            set
            {
                if (_privilegeid != value)
                {
                    _privilegeid = value;
                    OnPropertyChanged("PrivilegeId");
                }
            }
        }

        [ColumnName("CURRENCY")]
        [Caption("CURRENCY")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string Currency
        {
            get
            {
                return _currency;
            }
            set
            {
                if (_currency != value)
                {
                    _currency = value;
                    OnPropertyChanged("Currency");
                }
            }
        }

        [ColumnName("FEELEVELTYPE")]
        [Range(typeof(FeeLevelTypes), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public FeeLevelTypes FeeLevelType
        {
            get
            {
                return _feeleveltype;
            }
            set
            {
                if (_feeleveltype != value)
                {
                    _feeleveltype = value;
                    OnPropertyChanged("FeeLevelType");
                }
            }
        }

        [ColumnName("COMISSIONAMOUNT")]
        [Caption("ComissionAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal ComissionAmount
        {
            get
            {
                return _comissionamount;
            }
            set
            {
                if (_comissionamount != value)
                {
                    _comissionamount = value;
                    OnPropertyChanged("ComissionAmount");
                }
            }
        }

        [ColumnName("STANDARTAMOUNT")]
        [Caption("StandartAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal StandartAmount
        {
            get
            {
                return _standartamount;
            }
            set
            {
                if (_standartamount != value)
                {
                    _standartamount = value;
                    OnPropertyChanged("StandartAmount");
                }
            }
        }

        [ColumnName("TOTALAMOUNT")]
        [Caption("TotalAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal TotalAmount
        {
            get
            {
                return _totalamount;
            }
            set
            {
                if (_totalamount != value)
                {
                    _totalamount = value;
                    OnPropertyChanged("TotalAmount");
                }
            }
        }

        [ColumnName("TAXAMOUNT")]
        [Caption("TaxAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal TaxAmount
        {
            get
            {
                return _taxamount;
            }
            set
            {
                if (_taxamount != value)
                {
                    _taxamount = value;
                    OnPropertyChanged("TaxAmount");
                }
            }
        }

        [ColumnName("FEEAMOUNT")]
        [Caption("FeeAmount")]
        [Range(typeof(decimal), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public decimal FeeAmount
        {
            get
            {
                return _feeamount;
            }
            set
            {
                if (_feeamount != value)
                {
                    _feeamount = value;
                    OnPropertyChanged("FeeAmount");
                }
            }
        }

        [ColumnName("FEESOURCE")]
        [Range(typeof(FeeSourceType), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public FeeSourceType FeeSource
        {
            get
            {
                return _feesource;
            }
            set
            {
                if (_feesource != value)
                {
                    _feesource = value;
                    OnPropertyChanged("FeeSource");
                }
            }
        }

        [ColumnName("CHARGECODE")]
        [Caption("ChargeCode")]
        [StringLength(MinLength = 0L, MaxLength = 0L)]
        [DataMember(EmitDefaultValue = false)]
        public string ChargeCode
        {
            get
            {
                return _chargecode;
            }
            set
            {
                if (_chargecode != value)
                {
                    _chargecode = value;
                    OnPropertyChanged("ChargeCode");
                }
            }
        }

        [ColumnName("VFALOGCONTROLID")]
        [Required(true)]
        [Range(typeof(long), Minimum = 0, Maximum = 0)]
        [DataMember(EmitDefaultValue = false)]
        public long VfaLogControlId
        {
            get
            {
                return _vfalogcontrolid;
            }
            set
            {
                if (_vfalogcontrolid != value)
                {
                    _vfalogcontrolid = value;
                    OnPropertyChanged("VfaLogControlId");
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
            DTORequestLogDetail dTORequestLogDetail = new DTORequestLogDetail();
            dTORequestLogDetail.ID = ID;
            dTORequestLogDetail.VfaLogControlId = VfaLogControlId;
            dTORequestLogDetail.ChargeCode = ChargeCode;
            dTORequestLogDetail.FeeSource = FeeSource;
            dTORequestLogDetail.FeeAmount = FeeAmount;
            dTORequestLogDetail.TaxAmount = TaxAmount;
            dTORequestLogDetail.TotalAmount = TotalAmount;
            dTORequestLogDetail.StandartAmount = StandartAmount;
            dTORequestLogDetail.ComissionAmount = ComissionAmount;
            dTORequestLogDetail.FeeLevelType = FeeLevelType;
            dTORequestLogDetail.Currency = Currency;
            dTORequestLogDetail.PrivilegeId = PrivilegeId;
            dTORequestLogDetail.BankAmount = BankAmount;
            dTORequestLogDetail.FillBaseProperties(this);
            return dTORequestLogDetail;
        }
    }

}
