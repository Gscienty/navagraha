import React from 'react';
import { Table, Tag, Button, Drawer, List, Modal } from 'antd';
import { connect } from 'react-redux';
import {
    deleteRepo,
    fetchFuncRepoList,
    FUNC_REPO_LIST_UNSET,
} from '../actions/repo';

class FuncRepoList extends React.PureComponent {

    FRESH_INTERVAL = 1000;
    WAITING_HANDLER = 0;

    state = {
        deleteMultiVersionsVisible: false,
        deleteMultiVersionsTitle: '',
        deleteMultiVersions: [],
    };

    constructor(props) {
        super(props);

        if (this.props.repo.state === FUNC_REPO_LIST_UNSET) {
            this.props.dispatch(fetchFuncRepoList());
        }

        this.WAITING_HANDLER = setInterval(() => {
            this.props.dispatch(fetchFuncRepoList());
        }, this.FRESH_INTERVAL);
    }

    deleteMultiVersionsDrawerOnClose = () => {
        this.setState({
            deleteMultiVersions: [],
            deleteMultiVersionsTitle: '',
            deleteMultiVersionsVisible: false,
        });
    };

    componentWillUnmount() {
        clearInterval(this.WAITING_HANDLER);
    }

    render() {

        const COLUMNS = [
            {
                title: '函数名称',
                dataIndex: 'repoName',
                key: 'repoName'
            },
            {
                title: '版本',
                key: 'repoVersions',
                render: n => (<div>{n.repoVersions.map(v => <Tag key={v}>{v}</Tag>)}</div>)
            },
            {
                title: '操作',
                key: 'operation',
                render: n => (
                    <div>
                        <Button
                            onClick={() => {
                                if (n.repoVersions.length === 1) {
                                    this.props.dispatch(deleteRepo(n.repoName, n.repoVersions[0]));
                                }
                                else {
                                    this.setState({
                                        deleteMultiVersionsVisible: true,
                                        deleteMultiVersionsTitle: n.repoName,
                                        deleteMultiVersions: n.repoVersions
                                    });
                                }
                            }}
                            size="small">
                            删除
                        </Button>
                    </div>
                )
            }
        ];

        let dataSource = [];
        this.props.repo.repo.filter(n => n.name !== '<none>').map(n => dataSource.push({
            key: n.name,
            repoName: n.name,
            repoVersions: n.versions
        }))
        
        return (
            <div>
                <Table columns={COLUMNS} dataSource={dataSource} />
                <Drawer
                    visible={this.state.deleteMultiVersionsVisible}
                    title={`删除 ${this.state.deleteMultiVersionsTitle}`}
                    onClose={this.deleteMultiVersionsDrawerOnClose}>
                    <List
                        itemLayout="horizontal"
                        dataSource={this.state.deleteMultiVersions}
                        renderItem={item => (<List.Item key={item}>
                                                <Button
                                                    type="link"
                                                    onClick={() => Modal.confirm({
                                                        title: '删除确认',
                                                        content: `确认是否删除${this.state.deleteMultiVersionsTitle} 版本${item}?`,
                                                        onOk: () => {
                                                            this.props.dispatch(deleteRepo(this.state.deleteMultiVersionsTitle, item));
                                                        }
                                                    })}>
                                                        {item}
                                                    </Button>
                                             </List.Item>)}/>

                </Drawer>
            </div>);
    }
};

export default connect(({ repo }) => ({
    repo: repo.funcRepo
}))(FuncRepoList);


