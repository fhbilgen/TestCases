using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [AttributeUsage(AttributeTargets.Property, AllowMultiple = false, Inherited = false)]
    public sealed class RequiredAttribute : AttributeBase
    {
        public bool AllowEmptyStrings { get; set; }

        public RequiredAttribute()
        {
        }

        public RequiredAttribute(bool allowEmptyStrings)
            : this()
        {
            AllowEmptyStrings = allowEmptyStrings;
        }

        public override ValidationResult IsValid(object value)
        {
            base.ErrorCode = "PEAK ISREQUIRED";
            base.ErrorMessage = "Object must not be null";
            if (value == null)
            {
                return GetInvalidResult();
            }
            if (value is string && !AllowEmptyStrings)
            {
                if (string.IsNullOrEmpty((string)value))
                {
                    return GetInvalidResult();
                }
                return GetValidResult();
            }
            return new ValidationResult
            {
                IsValid = true
            };
        }
    }
}
