public enum TbmsfVfaMatchType : byte
{
    Different,
    Same,
    Ignored
}

public enum IsSuccessful : byte
{
    False,
    True
}

[Serializable]
public enum LogTypes
{
    None,
    Update,
    Delete
}

// Peak.Common.VFA.Enums.TbmsfFeeControl
public enum TbmsfFeeControl : byte
{
    False,
    True
}

public enum NoFeeTypes : byte
{
    None,
    OnlyTbmsf,
    OnlyVfa,
    All
}

public enum FeeSourceType : byte
{
    None,
    Vfa,
    Tbmsf
}

[Serializable]
public enum CalendarTypes : byte
{
    None,
    Country,
    Currency
}

[Serializable]
public enum WeekDays : byte
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
}

public enum DayTypes
{
    None,
    WorkingDays,
    Holidays,
    All,
    AllDaysWithMarkedHolidays
}

[Serializable]
public enum Languages : byte
{
    None,
    Turkish,
    English,
    German,
    French,
    Arabic
}

public enum CalendarHolidayWorkflowTypes : byte
{
    None,
    Insert,
    Update,
    Delete
}

public enum CalendarHolidayTypes : byte
{
    NonPermanentHoliday,
    PermanentHoliday,
    AllHolidays
}


[Serializable]
public enum FeeLevelTypes : byte
{
    None,
    CustomerFeeWaiver,
    AccountFeeWaiver,
    CustomerException,
    AccountException,
    SalaryProtocol,
    NonSalaryProtocol,
    StandardPricewithQualifier,
    StandardPrice,
    FeePackage,
    Commitment,
    Campaign,
    Condition,
    CommitmentCondition,
    InstructionCondition,
    CampaignCondition,
    CriteriaGroup,
    FeeBox,
    DynamicPrivilige,
    PartialFeePackage,
    FeeCampaign
}

[Serializable]
public enum Channels : byte
{
    None = 0,
    Branch = 1,
    ATM = 2,
    POS = 3,
    Internet = 4,
    CallCenter = 5,
    Mobile = 6,
    VirtualPOS = 7,
    IVR = 8,
    RegularPayment = 9,
    Unit = 10,
    WebServiceBanking = 11,
    OtherBankATM = 12,
    OtherBankPOS = 13,
    OnSiteBanking = 14,
    CallCenterIntegration = 15,
    ScheduledOperations = 51,
    PeriodicOperation = 52,
    EventHandler = 53,
    Integration = 54,
    AsynchronousOperation = 55,
    OperationCenter = 56,
    BusinessPartners = 57,
    WebChannels = 58,
    QueueMatic = 59,
    CentralCollection = 60,
    VITMobil = 61,
    SesliIVR = 62,
    WebChat = 63,
    ApiGateway = 64,
    MobileAssistant = 65,
    CommonATM = 66,
    DigitalBank = 67,
    EbisDestekWebChat = 68,
    TellerTablet = 69,
    CepteKazan = 70,
    VGO = 71,
    DigitalInPocket = 72
}