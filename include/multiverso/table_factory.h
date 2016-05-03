#ifndef MULTIVERSO_TABLE_FACTORY_H_
#define MULTIVERSO_TABLE_FACTORY_H_

#include "multiverso/table_interface.h"

#include <string>

namespace multiverso {
enum EleType {
  kInt = 0, kFloat, kDouble
};

typedef WorkerTable* (*worker_table_creater_t)(void**table_args);
typedef ServerTable* (*server_table_creater_t)(void**table_args);

class TableFactory {
public:
  static WorkerTable* CreateTable(
    EleType ele_type,
    std::string& type, 
    void**table_args);
  static WorkerTable* CreateTable(
    EleType ele_type1,
    EleType ele_type2,
    std::string& type,
    void**table_args);
  static void RegisterTable(
    std::string& type,
    worker_table_creater_t wt,
    server_table_creater_t st);
private:
  static WorkerTable* CreateTable(
    std::string& type,
    void**table_args);
  TableFactory() = default;
  static std::unordered_map<
    std::string,
    std::pair<worker_table_creater_t,
    server_table_creater_t> > table_creaters_;
};

namespace table_factory {
struct TableRegister {
  TableRegister(std::string type, worker_table_creater_t wt,
    server_table_creater_t st) {
    TableFactory::RegisterTable(type, wt, st);
  }
};
} // namespace table_factory

} // namespace multiverso

#endif // MULTIVERSO_TABLE_FACTORY_H_


//#ifndef MULTIVERSO_INCLUDE_TABLE_FACTORY_H_
//#define MULTIVERSO_INCLUDE_TABLE_FACTORY_H_
//
//#include <functional>
//#include <string>
//#include <map>
//
//#include "multiverso/util/log.h"
//#include "multiverso/table/array_table.h"
//
//namespace multiverso {
//
//class WorkerTable;
//
//class TableFactory {
//public:
//  virtual WorkerTable* CreateTable(const std::string& args) = 0;
//  static TableFactory* GetFactory(const std::string& type);
//};
//
//
//void MV_CreateTable(const std::string& type, const std::string& args, void** out) {
//  TableFactory* tf = TableFactory::GetFactory(type);
//  *out = static_cast<void*>(tf->CreateTable(args));
//}
//
//class ArrayTableFactory : public TableFactory {
//public:
//  WorkerTable* CreateTable(const std::string& args) override {
//    // new ArrayServer()
//  }
//}
//// TODO(feiga): Refine
//
//// TODO(feiga): provide better table creator method
//// Abstract Factory to create server and worker
////class TableFactory {
////  // static TableFactory* GetTableFactory();
////  virtual WorkerTable* CreateWorker() = 0;
////  virtual ServerTable* CreateServer() = 0;
////  static TableFactory* fatory_;
////};
//
////namespace table {
//
////}
//
////class TableBuilder {
////public:
////  TableBuilder& SetArribute(const std::string& name, const std::string& val);
////  WorkerTable* WorkerTableBuild();
////  ServerTable* ServerTableBuild();
////private:
////  std::string Get(const std::string& name) const;
////  std::unordered_map<std::string, std::string> params_;
////};
//
////class Context {
////public:
////  Context& SetArribute(const std::string& name, const std::string& val);
////  
////  int get_int(const std::string& name)  {
////    CHECK(params_.find(name) != params_.end());
////    return atoi(params_[name].c_str());
////  }
////
////private:
////  std::string get(const std::string& name) const;
////  std::map<std::string, std::string> params_;
////};
////
////class WorkerTable;
////
////class TableRegistry {
////public:
////  typedef WorkerTable* (*Creator)(const Context&);
////  typedef std::map<std::string, Creator> Registry;
////  static TableRegistry* Global();
////
////  static void AddCreator(const std::string& type, Creator creator) {
////    Registry& r = registry(); 
////    r[type] = creator;
////  }
////  
////  static Registry& registry() {
////    static Registry instance;
////    return instance;
////  }
////
////  static WorkerTable* CreateTable(const std::string& type, const Context& context) {
////    Registry& r = registry(); 
////    return r[type](context);
////
////  }
////
////private:
////  TableRegistry() {}
////};
////
////class TableRegisterer {
////public:
////  TableRegisterer(const std::string& type,
////                  WorkerTable* (*creator)(const Context&)) {
////    TableRegistry::AddCreator(type, creator);
////  }
////};
////
////#define REGISTER_TABLE_CREATOR(type, creator) \
////  static TableRegisterer(type, creator) g_creator_##type(#type, creator); 
////  
//}
//
//#endif // MULTIVERSO_INCLUDE_TABLE_FACTORY_H_