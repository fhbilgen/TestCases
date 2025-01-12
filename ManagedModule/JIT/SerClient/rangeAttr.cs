using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [AttributeUsage(AttributeTargets.Property, AllowMultiple = false, Inherited = false)]
    public sealed class RangeAttribute : AttributeBase
    {
        public Type OperandType { get; set; }

        public object Maximum { get; set; }

        public object Minimum { get; set; }

        public RangeAttribute(Type operandType, object minimum, object maximum)
        {
            OperandType = operandType;
            Minimum = minimum;
            Maximum = maximum;
        }

        public RangeAttribute(Type operandType)
        {
            OperandType = operandType;
        }

        public override ValidationResult IsValid(object value)
        {
            if (value is short || value is int || value is long)
            {
                return IsValid(long.Parse(value.ToString()));
            }
            if (value is decimal)
            {
                return IsValid(decimal.Parse(value.ToString()));
            }
            if (value is double)
            {
                return IsValid(double.Parse(value.ToString()));
            }
            if (value is DateTime)
            {
                return IsValid(DateTime.Parse(value.ToString()));
            }
            throw new Exception(string.Format("Type {0} is not defined to compare", value.GetType().FullName));
        }

        private ValidationResult IsValid(long value)
        {
            ValidationResult validationResult = IsComparable();
            if (validationResult == null)
            {
                if (Maximum == null)
                {
                    long num = long.Parse(Minimum.ToString());
                    if (value < num)
                    {
                        string format = "Property Value {0} must be bigger than Minimum  {1}";
                        base.ErrorMessage = string.Format(format, value, Minimum);
                        return GetInvalidResult();
                    }
                    return GetValidResult();
                }
                if (Minimum == null)
                {
                    long num2 = long.Parse(Maximum.ToString());
                    if (value > num2)
                    {
                        string format2 = "Property Value {0} must be less than Maximum  {1}";
                        base.ErrorMessage = string.Format(format2, value, Maximum);
                        return GetInvalidResult();
                    }
                    return GetValidResult();
                }
                long num3 = long.Parse(Minimum.ToString());
                long num4 = long.Parse(Maximum.ToString());
                if (value >= num3 && value <= num4)
                {
                    return GetValidResult();
                }
                string format3 = "Property Value {0} must be bigger than Minimum  {1} and less than Maximum {2}";
                base.ErrorMessage = string.Format(format3, value, Minimum, Maximum);
                return GetInvalidResult();
            }
            return validationResult;
        }

        private ValidationResult IsValid(double value)
        {
            ValidationResult validationResult = IsComparable();
            if (validationResult == null)
            {
                if (Maximum == null)
                {
                    double num = double.Parse(Minimum.ToString());
                    if (value < num)
                    {
                        string format = "Property Value {0} must be bigger than Minimum  {1}";
                        base.ErrorMessage = string.Format(format, value, Minimum);
                        return GetInvalidResult();
                    }
                    return GetInvalidResult();
                }
                if (Minimum == null)
                {
                    double num2 = double.Parse(Maximum.ToString());
                    if (value > num2)
                    {
                        string format2 = "Property Value {0} must be less than Maximum  {1}";
                        base.ErrorMessage = string.Format(format2, value, Maximum);
                        return GetInvalidResult();
                    }
                    return GetValidResult();
                }
                double num3 = double.Parse(Minimum.ToString());
                double num4 = double.Parse(Maximum.ToString());
                if (value >= num3 && value <= num4)
                {
                    return GetValidResult();
                }
                string format3 = "Property Value {0} must be bigger than Minimum  {1} and less than Maximum {2}";
                base.ErrorMessage = string.Format(format3, value, Minimum, Maximum);
                return GetInvalidResult();
            }
            return validationResult;
        }

        private ValidationResult IsValid(decimal value)
        {
            ValidationResult validationResult = IsComparable();
            if (validationResult == null)
            {
                if (Maximum == null)
                {
                    decimal num = decimal.Parse(Minimum.ToString());
                    if (value < num)
                    {
                        string format = "Property Value {0} must be bigger than Minimum  {1}";
                        base.ErrorMessage = string.Format(format, value, Minimum);
                        return GetInvalidResult();
                    }
                    return GetInvalidResult();
                }
                if (Minimum == null)
                {
                    decimal num2 = decimal.Parse(Maximum.ToString());
                    if (value > num2)
                    {
                        string format2 = "Property Value {0} must be less than Maximum  {1}";
                        base.ErrorMessage = string.Format(format2, value, Maximum);
                        return GetInvalidResult();
                    }
                    return GetValidResult();
                }
                decimal num3 = decimal.Parse(Minimum.ToString());
                decimal num4 = decimal.Parse(Maximum.ToString());
                if (value >= num3 && value <= num4)
                {
                    return GetValidResult();
                }
                string format3 = "Property Value {0} must be bigger than Minimum  {1} and less than Maximum {2}";
                base.ErrorMessage = string.Format(format3, value, Minimum, Maximum);
                return GetInvalidResult();
            }
            return validationResult;
        }

        private ValidationResult IsValid(DateTime value)
        {
            ValidationResult validationResult = IsComparable();
            if (validationResult == null)
            {
                if (Maximum == null)
                {
                    DateTime dateTime = DateTime.Parse(Minimum.ToString());
                    if (value < dateTime)
                    {
                        string format = "Property Value {0} must be bigger than Minimum  {1}";
                        base.ErrorMessage = string.Format(format, value, Minimum);
                        return GetInvalidResult();
                    }
                    return GetInvalidResult();
                }
                if (Minimum == null)
                {
                    DateTime dateTime2 = DateTime.Parse(Maximum.ToString());
                    if (value > dateTime2)
                    {
                        string format2 = "Property Value {0} must be less than Maximum  {1}";
                        base.ErrorMessage = string.Format(format2, value, Maximum);
                        return GetInvalidResult();
                    }
                    return GetValidResult();
                }
                DateTime dateTime3 = DateTime.Parse(Minimum.ToString());
                DateTime dateTime4 = DateTime.Parse(Maximum.ToString());
                if (value >= dateTime3 && value <= dateTime4)
                {
                    return GetValidResult();
                }
                string format3 = "Property Value {0} must be bigger than Minimum  {1} and less than Maximum {2}";
                base.ErrorMessage = string.Format(format3, value, Minimum, Maximum);
                return GetInvalidResult();
            }
            return validationResult;
        }

        private ValidationResult IsComparable()
        {
            if (Maximum == null && Minimum == null)
            {
                throw new Exception("There is no maximum or minimum value to compare");
            }
            if (Maximum != null)
            {
                Type type = Maximum.GetType();
                if (!OperandType.IsAssignableFrom(type))
                {
                    throw new Exception(string.Format("Provided Maximum value type {0} cannot be casted the type {1}", type.FullName, OperandType.FullName));
                }
            }
            if (Minimum != null)
            {
                Type type2 = Minimum.GetType();
                if (!OperandType.IsAssignableFrom(type2))
                {
                    throw new Exception(string.Format("Provided Minimum value type {0} cannot be casted the type {1}", type2.FullName, OperandType.FullName));
                }
            }
            return null;
        }
    }

}
