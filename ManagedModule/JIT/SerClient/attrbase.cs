using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    public class ValidationResult
    {
        public string Message { get; set; }

        public string MessageCode { get; set; }

        public bool IsValid { get; set; }
    }


    [Serializable]
    public class AttributeBase : Attribute
    {
        public string ErrorMessage { get; set; }

        public string ErrorCode { get; set; }

        protected ValidationResult GetInvalidResult()
        {
            return new ValidationResult
            {
                MessageCode = ErrorCode,
                Message = ErrorMessage,
                IsValid = false
            };
        }

        protected ValidationResult GetValidResult()
        {
            return new ValidationResult
            {
                IsValid = true
            };
        }

        public virtual ValidationResult IsValid(object value)
        {
            throw new Exception("Not Implemented");
        }
    }

}
