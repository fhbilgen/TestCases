using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [Serializable]
    [DataContract(Name = "A")]
    public class BaseDataTransferObject : INotifyPropertyChanged, IDataTransferObject
    {
        private string _recordUserCode;

        private string _recordBranchCode;
        private string _recordScreenCode;

        private DateTime _recordDate;

        private Guid _recordRequestObjectId;

        private Channels _recordChannelCode;

        private string _logUserCode;

        private DateTime _logDate;

        private LogTypes _logType;

        private readonly string _uniquePropertyName;

        [DataMember(Name = "A", EmitDefaultValue = false)]
        [ColumnName("RECORDUSERCODE")]
        public string RecordUserCode
        {
            get
            {
                return _recordUserCode;
            }
            set
            {
                if (_recordUserCode != value)
                {
                    _recordUserCode = value;
                    OnPropertyChanged("RecordUserCode");
                }
            }
        }

        [DataMember(Name = "B", EmitDefaultValue = false)]
        public string RecordBranchCode
        {
            get
            {
                return _recordBranchCode;
            }
            set
            {
                if (_recordBranchCode != value)
                {
                    _recordBranchCode = value;
                    OnPropertyChanged("RecordBranchCode");
                }
            }
        }

        [DataMember(Name = "C", EmitDefaultValue = false)]
        [IsVisibleInHistoryGrid(false)]
        public string RecordScreenCode
        {
            get
            {
                return _recordScreenCode;
            }
            set
            {
                if (_recordScreenCode != value)
                {
                    _recordScreenCode = value;
                    OnPropertyChanged("RecordScreenCode");
                }
            }
        }

        [DataMember(Name = "D", EmitDefaultValue = false)]
        [ColumnName("RECORDDATE")]
        public DateTime RecordDate
        {
            get
            {
                return _recordDate;
            }
            set
            {
                if (_recordDate != value)
                {
                    _recordDate = value;
                    OnPropertyChanged("RecordDate");
                }
            }
        }

        [DataMember(Name = "E", EmitDefaultValue = false)]
        [IsVisibleInHistoryGrid(false)]
        public Guid RecordRequestObjectId
        {
            get
            {
                return _recordRequestObjectId;
            }
            set
            {
                if (_recordRequestObjectId != value)
                {
                    _recordRequestObjectId = value;
                    OnPropertyChanged("RecordRequestObjectId");
                }
            }
        }

        [DataMember(Name = "F", EmitDefaultValue = false)]
        [IsVisibleInHistoryGrid(false)]
        public Channels RecordChannelCode
        {
            get
            {
                return _recordChannelCode;
            }
            set
            {
                if (_recordChannelCode != value)
                {
                    _recordChannelCode = value;
                    OnPropertyChanged("RecordChannelCode");
                }
            }
        }

        [DataMember(Name = "G", EmitDefaultValue = false)]
        [ColumnName("LOGDATE")]
        public DateTime LogDate
        {
            get
            {
                return _logDate;
            }
            set
            {
                if (_logDate != value)
                {
                    _logDate = value;
                    OnPropertyChanged("LogDate");
                }
            }
        }

        [DataMember(Name = "H", EmitDefaultValue = false)]
        [ColumnName("LOGUSER")]
        public string LogUserCode
        {
            get
            {
                return _logUserCode;
            }
            set
            {
                if (_logUserCode != value)
                {
                    _logUserCode = value;
                    OnPropertyChanged("LogUserCode");
                }
            }
        }

        [DataMember(Name = "I", EmitDefaultValue = false)]
        [ColumnName("LOGTYPE")]
        public LogTypes LogType
        {
            get
            {
                return _logType;
            }
            set
            {
                if (_logType != value)
                {
                    _logType = value;
                    OnPropertyChanged("LogType");
                }
            }
        }

        [field: NonSerialized]
        public event PropertyChangedEventHandler PropertyChanged;

        public override string ToString()
        {
            if (_uniquePropertyName == null)
            {
                return base.ToString();
            }
            PropertyInfo property = GetType().GetProperty(_uniquePropertyName);
            if (property == null)
            {
                return base.ToString();
            }
            object value = property.GetValue(this, null);
            if (value == null)
            {
                return base.ToString();
            }
            return value.ToString();
        }

        public void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
            {
                this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        public void FillBaseProperties(BaseDataTransferObject source)
        {
            RecordBranchCode = source.RecordBranchCode;
            RecordDate = source.RecordDate;
            RecordRequestObjectId = source.RecordRequestObjectId;
            RecordScreenCode = source.RecordScreenCode;
            RecordUserCode = source.RecordUserCode;
            RecordChannelCode = source.RecordChannelCode;
            LogUserCode = source.LogUserCode;
            LogDate = source.LogDate;
            LogType = source.LogType;
        }

        public override bool Equals(object dto)
        {
            return compare(dto, false);
        }

        public bool Equals(object dto, bool includeInheritedProperties)
        {
            return compare(dto, includeInheritedProperties);
        }

        public List<string> Compare(object dto, bool includeInheritedProperties)
        {
            return findDifferentProperties(dto, includeInheritedProperties);
        }

        public List<string> Compare(object dto, bool includeInheritedProperties, bool excludeUnpersistentAttributes)
        {
            return findDifferentProperties(dto, includeInheritedProperties, excludeUnpersistentAttributes);
        }

        public BaseDataTransferObject Copy()
        {
            BaseDataTransferObject baseDataTransferObject = new BaseDataTransferObject();
            baseDataTransferObject.FillBaseProperties(this);
            return baseDataTransferObject;
        }

        private bool compare(object dto, bool includeInheritedProperties)
        {
            if (dto == null || dto.GetType() != GetType())
            {
                return false;
            }
            PropertyInfo[] array = ((!includeInheritedProperties) ? dto.GetType().GetProperties(BindingFlags.DeclaredOnly | BindingFlags.Instance | BindingFlags.Public) : dto.GetType().GetProperties(BindingFlags.Instance | BindingFlags.Public));
            foreach (PropertyInfo propertyInfo in array)
            {
                object obj = null;
                object obj2 = null;
                try
                {
                    obj = propertyInfo.GetValue(dto, null);
                    obj2 = propertyInfo.GetValue(this, null);
                }
                catch (TargetParameterCountException)
                {
                    obj = propertyInfo.GetValue(dto, new object[1]);
                    obj2 = propertyInfo.GetValue(this, new object[1]);
                }
                if (!Convert.ToString(obj).Equals(Convert.ToString(obj2)))
                {
                    return false;
                }
            }
            return true;
        }

        private List<string> findDifferentProperties(object dto, bool includeInheritedProperties, bool excludeUnpersistentAttributes = false)
        {
            if (dto == null || dto.GetType() != GetType())
            {
                throw new Exception("DTO tipleri farklı.");
            }
            List<string> list = new List<string>();
            PropertyInfo[] array = ((!includeInheritedProperties) ? dto.GetType().GetProperties(BindingFlags.DeclaredOnly | BindingFlags.Instance | BindingFlags.Public) : dto.GetType().GetProperties(BindingFlags.Instance | BindingFlags.Public));
            if (excludeUnpersistentAttributes)
            {
                List<PropertyInfo> list2 = new List<PropertyInfo>();
                PropertyInfo[] array2 = array;
                foreach (PropertyInfo propertyInfo in array2)
                {
                    if (Attribute.IsDefined(propertyInfo, typeof(ColumnNameAttribute)))
                    {
                        list2.Add(propertyInfo);
                    }
                }
                array = list2.ToArray();
            }
            foreach (PropertyInfo propertyInfo2 in array)
            {
                object value;
                object value2;
                try
                {
                    value = propertyInfo2.GetValue(dto, null);
                    value2 = GetType().GetProperty(propertyInfo2.Name).GetValue(this, null);
                }
                catch (TargetParameterCountException)
                {
                    value = propertyInfo2.GetValue(dto, new object[1]);
                    value2 = GetType().GetProperty(propertyInfo2.Name).GetValue(this, new object[1]);
                }
                if (!Convert.ToString(value).Equals(Convert.ToString(value2)))
                {
                    list.Add(propertyInfo2.Name);
                }
            }
            return list;
        }
    }

}
