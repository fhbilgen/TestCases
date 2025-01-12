using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [AttributeUsage(AttributeTargets.Property, AllowMultiple = false, Inherited = false)]
    public sealed class StringLengthAttribute : AttributeBase
    {
        public long MaxLength { get; set; }

        public long MinLength { get; set; }

        public StringLengthAttribute()
        {
            base.ErrorCode = "Peak String Length";
        }

        public StringLengthAttribute(long minLength, long maxLegth)
            : this()
        {
            MinLength = minLength;
            MaxLength = maxLegth;
        }

        public override ValidationResult IsValid(object value)
        {
            if (MaxLength < MinLength)
            {
                throw new Exception(string.Format("MaxLength  must be bigger than MinLength ", MaxLength, MinLength));
            }
            string text = value as string;
            if (text == null)
            {
                return new ValidationResult
                {
                    IsValid = false,
                    Message = "String is null, its length cannot be compared"
                };
            }
            if (MaxLength != 0L)
            {
                string format = "String Length must be more than {0} and less than {1}";
                if (text.Length < MinLength || text.Length > MaxLength)
                {
                    base.ErrorMessage = string.Format(format, MinLength, MaxLength);
                    return GetInvalidResult();
                }
            }
            else if (text.Length < MinLength)
            {
                string format2 = "String Length must be more than {0}";
                base.ErrorMessage = string.Format(format2, MinLength);
                return GetInvalidResult();
            }
            return GetValidResult();
        }
    }

}
