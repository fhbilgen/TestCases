using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    public interface IParameterDataTransferObject
    {
        string ParameterMainGroupCode { get; set; }

        string ParameterCode { get; set; }

        string ParameterDescription { get; set; }

        string ParameterDetail1 { get; set; }

        string ParameterDetail2 { get; set; }

        string ParameterDetail3 { get; set; }

        string ParameterDetail4 { get; set; }

        string ParameterDetail5 { get; set; }

        string ParameterDetail6 { get; set; }

        string ParameterDetail7 { get; set; }

        string ParameterDetail8 { get; set; }

        string ParameterDetail9 { get; set; }

        string ParameterDetail10 { get; set; }
    }


    [Serializable]
    [DataContract]
    public class DTOCalendar : BaseDataTransferObject, IParameterDataTransferObject, IDataTransferObject
    {
        private string _code;

        private CalendarTypes _calendarType;

        private string _calendarDescription;

        private WeekDays _officialHoliday1;

        private WeekDays _officialHoliday2;

        private DateTime _appDateTime;

        private double _days;

        private bool _isSucceeded;

        [DataMember(EmitDefaultValue = false)]
        public string ParameterMainGroupCode { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterGroupCode { get; set; }

        public string ParameterCode
        {
            get
            {
                return Code;
            }
            set
            {
                Code = value;
            }
        }

        public string ParameterDescription
        {
            get
            {
                return CalendarDescription;
            }
            set
            {
                CalendarDescription = value;
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail1 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail2 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail3 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail4 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail5 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail6 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail7 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail8 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail9 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public string ParameterDetail10 { get; set; }

        [DataMember(EmitDefaultValue = false)]
        public DateTime AppDateTime
        {
            get
            {
                return _appDateTime;
            }
            set
            {
                if (_appDateTime != value)
                {
                    _appDateTime = value;
                }
            }
        }

        [Required(true)]
        [StringLength(MinLength = 0L, MaxLength = 3L)]
        [DataMember(EmitDefaultValue = false)]
        public string Code
        {
            get
            {
                return _code;
            }
            set
            {
                if (_code != value)
                {
                    _code = value;
                    OnPropertyChanged("Code");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public CalendarTypes CalendarType
        {
            get
            {
                return _calendarType;
            }
            set
            {
                if (_calendarType != value)
                {
                    _calendarType = value;
                    OnPropertyChanged("CalendarType");
                }
            }
        }

        [StringLength(MinLength = 0L, MaxLength = 100L)]
        [DataMember(EmitDefaultValue = false)]
        public string CalendarDescription
        {
            get
            {
                return _calendarDescription;
            }
            set
            {
                if (_calendarDescription != value)
                {
                    _calendarDescription = value;
                    OnPropertyChanged("CalendarDescription");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public WeekDays OfficialHoliday1
        {
            get
            {
                return _officialHoliday1;
            }
            set
            {
                if (_officialHoliday1 != value)
                {
                    _officialHoliday1 = value;
                    OnPropertyChanged("OfficialHoliday1");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public WeekDays OfficialHoliday2
        {
            get
            {
                return _officialHoliday2;
            }
            set
            {
                if (_officialHoliday2 != value)
                {
                    _officialHoliday2 = value;
                    OnPropertyChanged("OfficialHoliday2");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public double Days
        {
            get
            {
                return _days;
            }
            set
            {
                if (_days != value)
                {
                    _days = value;
                    OnPropertyChanged("Days");
                }
            }
        }

        [DataMember(EmitDefaultValue = false)]
        public bool IsSucceeded
        {
            get
            {
                return _isSucceeded;
            }
            set
            {
                if (_isSucceeded != value)
                {
                    _isSucceeded = value;
                    OnPropertyChanged("IsSucceeded");
                }
            }
        }

        public new BaseDataTransferObject Copy()
        {
            DTOCalendar dTOCalendar = new DTOCalendar();
            dTOCalendar.Code = Code;
            dTOCalendar.CalendarType = CalendarType;
            dTOCalendar.CalendarDescription = CalendarDescription;
            dTOCalendar.OfficialHoliday1 = OfficialHoliday1;
            dTOCalendar.OfficialHoliday2 = OfficialHoliday2;
            dTOCalendar.AppDateTime = AppDateTime;
            dTOCalendar.Days = Days;
            dTOCalendar.IsSucceeded = IsSucceeded;
            dTOCalendar.FillBaseProperties(this);
            return dTOCalendar;
        }
    }

}
